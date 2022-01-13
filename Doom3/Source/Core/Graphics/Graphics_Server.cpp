#include "Graphics_Server.h"

#include <functional>

#include "../Game/GameCore.h"
#include "../Scene/Layer.h"
#include "../Game/AssetManager/AssetManager.h"


#include "GraphicsAPI/Manager/GraphicsAPIManager.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "Buffer/UniformBufferObjectManager.h"

#include <Rendering/Renderer/Renderer.h>
#include <Rendering/Light/Light.h>
#include "FrameBuffer/DefferedRenderingFrameBuffer.h"
#include <Rendering/Renderer/RendererStaticIterator.h>

#include "Rendering/Camera.h"

#include "Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"

#include "graphicsSetting.h"
#include "GraphicsAPI/graphicsAPISetting.h"

#include "MainTimer.h"

#include "Acceleration/SortFrontToBackSolver.h"
#include "DebugGraphics/OverDrawVisualization.h"
#include "DebugGraphics/maskedOcclusionCullingTester.h"

#include <EngineGUI/GUIModules/MaskedOcclusionCulliingDebugger.h>

#include "Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.h"
#include "GraphicsAPI/eGraphicsAPIType.h"

//#define D_DEBUG_CPU_VENDOR_PROFILER

using namespace dooms::graphics;

bool Graphics_Server::InitializeGraphicsAPI()
{
	dooms::graphics::graphicsSetting::LoadData();
	dooms::graphics::graphicsAPISetting::LoadData();
	
	bool isSuccess = false;

	const std::string targetGraphicsAPI = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("Graphics", "GRAPHICS_API");
	if (targetGraphicsAPI == "OPENGL")
	{
		isSuccess = GraphicsAPIManager::Initialize(eGraphicsAPIType::OpenGL);
	}
	else if (targetGraphicsAPI == "DX11_10")
	{
		isSuccess = GraphicsAPIManager::Initialize(eGraphicsAPIType::DX11_10);
	}
	else
	{
		D_ASSERT(false);
	}
	D_ASSERT(isSuccess == true);
	return isSuccess;
}

void dooms::graphics::Graphics_Server::Init()
{
	
	
	dooms::ui::engineGUIServer::Initialize();

	mCullingSystem = std::make_unique<culling::EveryCulling>(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	mCullingSystem->SetThreadCount(resource::JobSystem::GetSingleton()->GetSubThreadCount() + 1);
	//mCullingSystem->mMaskedSWOcclusionCulling->mSolveMeshRoleStage.mOccluderViewSpaceBoundingSphereRadius = ConfigData::GetSingleton()->GetConfigData().GetValue<FLOAT32>("Graphics", "MASKED_OC_OCCLUDER_VIEW_SPACE_BOUNDING_SPHERE_RADIUS");
	mCullingSystem->mMaskedSWOcclusionCulling->mSolveMeshRoleStage.mOccluderAABBScreenSpaceMinArea = ConfigData::GetSingleton()->GetConfigData().GetValue<FLOAT32>("Graphics", "MASKED_OC_OCCLUDER_AABB_SCREEN_SPACE_MIN_AREA");


	dooms::ui::maskedOcclusionCulliingDebugger::Initilize(mCullingSystem->mMaskedSWOcclusionCulling.get());

	return;
}

void dooms::graphics::Graphics_Server::LateInit()
{
#ifdef DEBUG_DRAWER
	mDebugGraphics.Init();
#endif 

	mDeferredRenderingDrawer.Initialize();
	//mQueryOcclusionCulling.InitQueryOcclusionCulling();
	//mCullDistance.InitializeGraphisAPIInput();
}



void Graphics_Server::Update()
{
	PreRender();

#ifdef DEBUG_DRAWER
	mDebugGraphics.Update();
	mRenderingDebugger.DrawRenderingBoundingBox();
	mRenderingDebugger.UpdateInputForPrintDrawCallCounter();
#endif

	//auto t_start = std::chrono::high_resolution_clock::now();
	
	D_START_PROFILING(RENDER, dooms::profiler::eProfileLayers::Rendering);
	Render();
	D_END_PROFILING(RENDER);

	//Render();

	//auto t_end = std::chrono::high_resolution_clock::now();
	//FLOAT64 elapsed_time_ms = std::chrono::duration<FLOAT64, std::milli>(t_end - t_start).count();
	//dooms::ui::PrintText("elapsed tick count : %lf", elapsed_time_ms);

	PostRender();

	mRenderingDebugger.Update();
}

void Graphics_Server::OnEndOfFrame()
{
#ifdef DEBUG_DRAWER
	mDebugGraphics.Reset();
#endif

	graphics::GraphicsAPI::SwapBuffer();
}



Graphics_Server::Graphics_Server()
{

}

Graphics_Server::~Graphics_Server()
{
	dooms::ui::engineGUIServer::ShutDown();
}

void Graphics_Server::PreCullJob()
{
	// Never remove this
	// After CullJob is finished, when main thread start new cull job at next frame, other threads may works on previous frame cull job
	std::function<void()> func = [] {};
	auto waitThreadsJobFinished = dooms::resource::JobSystem::GetSingleton()->PushBackJobToAllThread(func);
	for (auto& waitThreadJobFinished : waitThreadsJobFinished)
	{
		waitThreadJobFinished.wait();
	}

	mCullingCameraCount = 0;

	D_START_PROFILING(mFrotbiteCullingSystem_ResetCullJobStat, dooms::profiler::eProfileLayers::Rendering);
	mCullingSystem->ResetCullJob();
	D_END_PROFILING(mFrotbiteCullingSystem_ResetCullJobStat);

}


void Graphics_Server::CameraCullJob(dooms::Camera* const camera)
{
	if (camera->GetIsCullJobEnabled() == true)
	{
		std::atomic_thread_fence(std::memory_order_acquire);

		culling::EveryCulling::GlobalDataForCullJob cullingSettingParameters;
		std::memcpy(cullingSettingParameters.mViewProjectionMatrix.data(), camera->GetViewProjectionMatrix().data(), sizeof(culling::Mat4x4));
		cullingSettingParameters.mFieldOfViewInDegree = camera->GetFieldOfViewInDegree();
		cullingSettingParameters.mCameraFarPlaneDistance = camera->GetClippingPlaneFar();
		cullingSettingParameters.mCameraNearPlaneDistance = camera->GetClippingPlaneNear();
		std::memcpy(cullingSettingParameters.mCameraWorldPosition.data(), camera->GetTransform()->GetPosition().data(), sizeof(culling::Vec3));
		std::memcpy(cullingSettingParameters.mCameraRotation.data(), camera->GetTransform()->GetRotation().data(), sizeof(culling::Vec4));

		mCullingSystem->UpdateGlobalDataForCullJob(camera->CameraIndexInCullingSystem, cullingSettingParameters);
		
		std::atomic_thread_fence(std::memory_order_release);
		
		resource::JobSystem::GetSingleton()->PushBackJobToAllThreadWithNoSTDFuture(std::function<void()>(mCullingSystem->GetThreadCullJobInLambda(camera->CameraIndexInCullingSystem)));
		D_START_PROFILING(CameraCullJob, dooms::profiler::eProfileLayers::Rendering);
		mCullingSystem->GetThreadCullJobInLambda(camera->CameraIndexInCullingSystem)();
		D_END_PROFILING(CameraCullJob);
	}
	
	

}


void Graphics_Server::DebugGraphics()
{
	if (graphicsSetting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger == true)
	{
		dooms::graphics::maskedOcclusionCullingTester::DebugBinnedTriangles(&(mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer));
	}

	if (graphicsSetting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger == true)
	{
		dooms::graphics::maskedOcclusionCullingTester::DebugTileCoverageMask(&(mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer));
	}

	if (graphicsSetting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger == true)
	{
		dooms::graphics::maskedOcclusionCullingTester::DebugTileL0MaxDepthValue(&(mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer));
	}
	
	/*
	const UINT32 tileCount = mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer.GetTileCount();
	const culling::Tile* const tiles = mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer.GetTiles();
	
	for(size_t tileIndex = 0 ; tileIndex < tileCount ; tileIndex++)
	{
		dooms::ui::maskedOcclusionCulliingDebugger::SetBinnedTriangleCount(tileIndex, tiles[tileIndex].mBinnedTriangleList.mCurrentTriangleCount);
	}
	*/

	mDebugGraphics.BufferVertexDataToGPU();
	mDebugGraphics.Draw();

}

void Graphics_Server::PreRenderRenderer()
{
	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(0);
	for (Renderer* renderer : renderersInLayer)
	{
		renderer->PreRender();
	}
}

void Graphics_Server::UpdateCameraIndexInCullingSystemOfCameraComponent()
{
	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();
	for (size_t cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];

		if (targetCamera->GetIsCullJobEnabled() == true)
		{
			targetCamera->CameraIndexInCullingSystem = mCullingCameraCount;

			mCullingCameraCount++;
		}
	}

	mCullingSystem->SetCameraCount(mCullingCameraCount);
}

void Graphics_Server::UpdateSortedEntityInfoListInCullingSystem()
{
	mCullingSystem->ResetSortedEntityCount();

	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();
	for (size_t cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];

		if (targetCamera->GetIsCullJobEnabled() == true)
		{
			size_t rendererCount = 0;
			const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(cameraIndex);
			for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
			{
				Renderer* const renderer = renderersInLayer[rendererIndex];
				if (IsValid(renderer) == true && renderer->GetIsComponentEnabled() == true)
				{
					mCullingSystem->SetSortedEntityInfo
					(
						targetCamera->CameraIndexInCullingSystem,
						rendererCount,
						renderer->mCullingEntityBlockViewer.GetTargetEntityBlock(),
						renderer->mCullingEntityBlockViewer.GetEntityIndexInBlock()
					);

					rendererCount++;
				}
			}
		}
	}
}

void Graphics_Server::PreRender()
{

	D_START_PROFILING(PreRenderRenderer, dooms::profiler::eProfileLayers::Rendering);
	PreRenderRenderer();
	D_END_PROFILING(PreRenderRenderer);

	UpdateCameraIndexInCullingSystemOfCameraComponent();
	UpdateSortedEntityInfoListInCullingSystem();

	
	

	dooms::ui::engineGUIServer::PreRender();
	if(Camera::GetMainCamera()->GetIsCullJobEnabled() == true)
	{
		D_START_PROFILING(PreCullJob, dooms::profiler::eProfileLayers::Rendering);
		PreCullJob();
		D_END_PROFILING(PreCullJob);
	}

	
}

void dooms::graphics::Graphics_Server::Render()
{
	//TODO : Think where put this, as early as good
	
	D_START_PROFILING(Update_Uniform_Buffer, dooms::profiler::eProfileLayers::Rendering);
	mUniformBufferObjectManager.UpdateUniformObjects();
	D_END_PROFILING(Update_Uniform_Buffer);
	
	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();

	FrameBuffer::UnBindFrameBuffer();
	//Clear ScreenBuffer
	
	for (size_t cameraIndex = 0 ; cameraIndex < spawnedCameraList.size() ; cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];

		if(targetCamera->GetIsCullJobEnabled() == true)
		{
			CameraCullJob(targetCamera); // do this first
		}
		


		D_ASSERT(IsValid(targetCamera));

		GraphicsAPI::ClearBufferColorBuffer(targetCamera->mDefferedRenderingFrameBuffer.GetFrameBufferID(), targetCamera->mClearColor[0], targetCamera->mClearColor[1], targetCamera->mClearColor[2], targetCamera->mClearColor[3]);
		GraphicsAPI::ClearBufferDepthBuffer(targetCamera->mDefferedRenderingFrameBuffer.GetFrameBufferID(), GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);

		targetCamera->UpdateUniformBufferObject();

		targetCamera->mDefferedRenderingFrameBuffer.ClearFrameBuffer(targetCamera);
		targetCamera->mDefferedRenderingFrameBuffer.BindFrameBuffer();
		
		D_START_PROFILING(RenderObject, dooms::profiler::eProfileLayers::Rendering);
		//GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
		RenderObject(targetCamera, cameraIndex);
		D_END_PROFILING(RenderObject);

		targetCamera->mDefferedRenderingFrameBuffer.UnBindFrameBuffer();
	
		// 
		//Blit DepthBuffer To ScreenBuffer

		if (targetCamera->IsMainCamera() == true)
		{
			//Only Main Camera can draw to screen buffer

			UpdateOverDrawVisualization(targetCamera, cameraIndex);


			targetCamera->mDefferedRenderingFrameBuffer.BlitDepthBufferToScreenBuffer();

			mPIPManager.DrawPIPs();

			targetCamera->mDefferedRenderingFrameBuffer.BindGBufferTextures();
			
			
			mDeferredRenderingDrawer.DrawDeferredRenderingQuadDrawer();
			

#ifdef DEBUG_DRAWER
			//�̰� ������ �������. �׳� ����� ����.
			
			DebugGraphics();
#endif
		}
		
	}

	RendererComponentStaticIterator::GetSingleton()->ChangeWorkingIndexRenderers();

#ifdef DEBUG_DRAWER
	mDebugGraphics.SetIsVertexDataSendToGPUAtCurrentFrame(false);
#endif


	D_START_PROFILING(engineGUIServer_Render, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::Render();
	D_END_PROFILING(engineGUIServer_Render);
	
}

void Graphics_Server::ProfilingCullingSystem()
{
#ifdef PROFILING_CULLING
	auto& profilingDatas = mCullingSystem->mEveryCullingProfiler.GetProfilingDatas();
	for(auto& data : profilingDatas)
	{
		const std::string cullingModuleTag{ data.first.data(), data.first.size() };
		dooms::profiling::profilingManager::AddProfilingData(cullingModuleTag.c_str(), (float)data.second.mElapsedTime);
	}
#endif
}

void Graphics_Server::PostRender()
{
	dooms::ui::engineGUIServer::PostRender();

	ProfilingCullingSystem();
}

void dooms::graphics::Graphics_Server::UpdateOverDrawVisualization(dooms::Camera* const targetCamera, const size_t cameraIndex)
{

#ifdef DEBUG_DRAWER
	OverDrawVisualization::ShowOverDrawVisualizationPIP(graphicsSetting::IsOverDrawVisualizationEnabled);
	if (graphicsSetting::IsOverDrawVisualizationEnabled == true)
	{
		OverDrawVisualization::SetOverDrawVisualizationRenderingState(true);
		RenderObject(targetCamera, cameraIndex);
		OverDrawVisualization::SetOverDrawVisualizationRenderingState(false);
	}
#endif

}



void dooms::graphics::Graphics_Server::RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex)
{
	D_ASSERT(IsValid(targetCamera) == true);

	targetCamera->UpdateUniformBufferObject();
	std::future<void> IsFinishedSortingReferernceRenderers;
	
	if (graphicsSetting::IsSortObjectFrontToBack == true)
	{
		math::Vector3 cameraPos = targetCamera->GetTransform()->GetPosition();

		D_START_PROFILING(CacheDistanceToCamera, dooms::profiler::eProfileLayers::Rendering);
		for (Renderer* renderer : dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer(cameraIndex))
		{
			renderer->CacheDistanceToCamera(cameraIndex, cameraPos);
		}
		D_END_PROFILING(CacheDistanceToCamera);

		//Push Multithread Sorting Renderer Front To Back  TO  JobSystem.
		IsFinishedSortingReferernceRenderers = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(std::function<void()>(dooms::graphics::SortFrontToBackSolver::GetSortRendererLambda(cameraIndex)));
	}

	D_START_PROFILING(DrawLoop, dooms::profiler::eProfileLayers::Rendering);
	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(cameraIndex);
		for (Renderer* renderer : renderersInLayer)
		{
			if
			(
				IsValid(renderer) == true && 
				renderer->GetOwnerEntityLayerIndex() == layerIndex && 
				renderer->GetIsComponentEnabled() == true
			)
			{
				if (
					targetCamera_IS_CULLED_flag_on == false ||
					renderer->GetIsCulled(targetCamera->CameraIndexInCullingSystem) == false
					)
				{
					//renderer->ColliderUpdater<dooms::physics::AABB3D>::GetWorldCollider()->DrawPhysicsDebugColor(eColor::Blue);
					renderer->Draw();
				}
			}
		}
	}
	D_END_PROFILING(DrawLoop);

	//Wait Multithread Sorting Renderer Front To Back  TO  JobSystem finished.
	if(IsFinishedSortingReferernceRenderers.valid() == true)
	{
		D_START_PROFILING(WAIT_SORTING_RENDERER_JOB, dooms::profiler::eProfileLayers::Rendering);
		IsFinishedSortingReferernceRenderers.wait();
		D_END_PROFILING(WAIT_SORTING_RENDERER_JOB);
	}

}



/*
void dooms::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	mCurrentRenderingMode = renderingMode;
	if (mCurrentRenderingMode == eRenderingMode::DeferredRendering)
	{
		mDeferredRenderingDrawer.InitializeGraphisAPIInput();
	}
}
*/



