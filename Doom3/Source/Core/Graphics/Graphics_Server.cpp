#include "Graphics_Server.h"

#include <functional>

#include "../Game/GameCore.h"
#include "../Scene/Layer.h"
#include "../Game/AssetManager/AssetManager.h"


#include "GraphicsAPI/Manager/GraphicsAPIManager.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "Buffer/UniformBufferObject/UniformBufferObjectManager.h"

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
#include "DebugGraphics/maskedOcclusionCullingTester.h"

#include <EngineGUI/GUIModules/MaskedOcclusionCulliingDebugger.h>

#include "Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.h"


bool dooms::graphics::Graphics_Server::InitializeGraphicsAPI(GraphicsAPI::eGraphicsAPIType graphicsAPIType)
{
	dooms::graphics::graphicsSetting::LoadData();
	dooms::graphics::graphicsAPISetting::LoadData();

	bool isSuccess = false;

	if(graphicsAPIType == GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE)
	{
		dooms::ui::PrintText("Read Target Graphics API from Config.ini file");

		const std::string targetGraphicsAPI = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("Graphics", "GRAPHICS_API");
		if (targetGraphicsAPI == "OPENGL")
		{
			graphicsAPIType = GraphicsAPI::eGraphicsAPIType::OpenGL;
		}
		else if (targetGraphicsAPI == "DX11_10" || targetGraphicsAPI == "DX11")
		{
			graphicsAPIType = GraphicsAPI::eGraphicsAPIType::DX11_10;
		}
		else
		{
			D_ASSERT(false);
		}
	}
	

	switch (graphicsAPIType)
	{
	case GraphicsAPI::eGraphicsAPIType::OpenGL:
		isSuccess = GraphicsAPIManager::Initialize(GraphicsAPI::eGraphicsAPIType::OpenGL);
		break;
	case GraphicsAPI::eGraphicsAPIType::DX11_10: 
		isSuccess = GraphicsAPIManager::Initialize(GraphicsAPI::eGraphicsAPIType::DX11_10);
		break;
	default:
		dooms::ui::PrintText("Graphics API isn't chosen. Default Graphics API OPENGL is chosen.");
		isSuccess = GraphicsAPIManager::Initialize(GraphicsAPI::eGraphicsAPIType::OpenGL); // If any specific api type isn't passed, just use opengl....
		D_ASSERT(false);
	}

	D_ASSERT(isSuccess == true);

	return isSuccess;
}

void dooms::graphics::Graphics_Server::Init(const int argc, char* const* const argv)
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



void dooms::graphics::Graphics_Server::Update()
{
	D_START_PROFILING(PreRender, dooms::profiler::eProfileLayers::Rendering);
	PreRender();
	D_END_PROFILING(PreRender);

#ifdef DEBUG_DRAWER

	D_START_PROFILING(mDebugGraphics_Update, dooms::profiler::eProfileLayers::Rendering);
	mDebugGraphics.Update();
	D_END_PROFILING(mDebugGraphics_Update);

	D_START_PROFILING(mRenderingDebugger_DrawRenderingBoundingBox, dooms::profiler::eProfileLayers::Rendering);
	mRenderingDebugger.DrawRenderingBoundingBox();
	D_END_PROFILING(mRenderingDebugger_DrawRenderingBoundingBox);
	
#endif

	//auto t_start = std::chrono::high_resolution_clock::now();

	D_START_PROFILING(RENDER, dooms::profiler::eProfileLayers::Rendering);
	Render();
	D_END_PROFILING(RENDER);

	//Render();

	//auto t_end = std::chrono::high_resolution_clock::now();
	//FLOAT64 elapsed_time_ms = std::chrono::duration<FLOAT64, std::milli>(t_end - t_start).count();
	//dooms::ui::PrintText("elapsed tick count : %lf", elapsed_time_ms);

	D_START_PROFILING(PostRender, dooms::profiler::eProfileLayers::Rendering);
	PostRender();
	D_END_PROFILING(PostRender);

	D_START_PROFILING(mRenderingDebugger_Update, dooms::profiler::eProfileLayers::Rendering);
	mRenderingDebugger.Update();
	D_END_PROFILING(mRenderingDebugger_Update);
}

void dooms::graphics::Graphics_Server::OnEndOfFrame()
{
#ifdef DEBUG_DRAWER
	mDebugGraphics.Reset();
#endif

	graphics::GraphicsAPI::SwapBuffer();
}


dooms::graphics::Graphics_Server::Graphics_Server()
{

}

dooms::graphics::Graphics_Server::~Graphics_Server()
{
	dooms::ui::engineGUIServer::ShutDown();
}

void dooms::graphics::Graphics_Server::PreCullJob()
{
	mCullingCameraCount = 0;

	D_START_PROFILING(CullingSystemPreCullJob, dooms::profiler::eProfileLayers::Rendering);
	mCullingSystem->PreCullJob();
	D_END_PROFILING(CullingSystemPreCullJob);

	D_START_PROFILING(UpdateCameraIndexInCullingSystemOfCameraComponent, dooms::profiler::eProfileLayers::Rendering);
	UpdateCameraIndexInCullingSystemOfCameraComponent();
	D_END_PROFILING(UpdateCameraIndexInCullingSystemOfCameraComponent);

}


void dooms::graphics::Graphics_Server::CameraCullJob(dooms::Camera* const camera)
{
	if (camera->GetIsCullJobEnabled() == true)
	{
		std::atomic_thread_fence(std::memory_order_acquire);

		culling::EveryCulling::GlobalDataForCullJob cullingSettingParameters;
		std::memcpy(cullingSettingParameters.mViewProjectionMatrix.data(), camera->GetViewProjectionMatrix(true).data(), sizeof(culling::Mat4x4));
		cullingSettingParameters.mFieldOfViewInDegree = camera->GetFieldOfViewInDegree();
		cullingSettingParameters.mCameraFarPlaneDistance = camera->GetClippingPlaneFar();
		cullingSettingParameters.mCameraNearPlaneDistance = camera->GetClippingPlaneNear();
		std::memcpy(cullingSettingParameters.mCameraWorldPosition.data(), camera->GetTransform()->GetPosition().data(), sizeof(culling::Vec3));
		std::memcpy(cullingSettingParameters.mCameraRotation.data(), camera->GetTransform()->GetRotation().data(), sizeof(culling::Vec4));

		mCullingSystem->UpdateGlobalDataForCullJob(camera->CameraIndexInCullingSystem, cullingSettingParameters);

		std::atomic_thread_fence(std::memory_order_release);

		std::function<void()> threadCullJob = [cullingSystem = mCullingSystem.get(), cameraIndexInCullingSystem = camera->CameraIndexInCullingSystem]()
		{
			cullingSystem->ThreadCullJob(cameraIndexInCullingSystem, dooms::resource::Thread::GetCallerSubThreadIndex() + 1);
		};

		auto futures = resource::JobSystem::GetSingleton()->PushBackJobToAllThread(threadCullJob);
		D_START_PROFILING(CameraCullJob, dooms::profiler::eProfileLayers::Rendering);
		mCullingSystem->ThreadCullJob(camera->CameraIndexInCullingSystem, 0);
		D_END_PROFILING(CameraCullJob);

		D_START_PROFILING(WaitSubThreadsCullJob, dooms::profiler::eProfileLayers::Rendering);
		for (auto& future : futures)
		{
			future.wait();
		}
		D_END_PROFILING(WaitSubThreadsCullJob);

	}



}


void dooms::graphics::Graphics_Server::DebugGraphics()
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

void dooms::graphics::Graphics_Server::PreRenderRenderer()
{
	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(0);
	for (Renderer* renderer : renderersInLayer)
	{
		renderer->PreRender();
	}
}

void dooms::graphics::Graphics_Server::UpdateCameraIndexInCullingSystemOfCameraComponent()
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

void dooms::graphics::Graphics_Server::PreRender()
{

	D_START_PROFILING(PreRenderRenderer, dooms::profiler::eProfileLayers::Rendering);
	PreRenderRenderer();
	D_END_PROFILING(PreRenderRenderer);

	D_START_PROFILING(engineGUIServer_PreRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::PreRender();
	D_END_PROFILING(engineGUIServer_PreRender);


	if (Camera::GetMainCamera()->GetIsCullJobEnabled() == true)
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

	for (size_t cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];
		D_ASSERT(IsValid(targetCamera));

		if (targetCamera->GetIsCullJobEnabled() == true)
		{
			CameraCullJob(targetCamera); // do this first
		}

		std::future<void> IsFinishedSortingReferernceRenderers;
		if (graphicsSetting::IsSortObjectFrontToBack == true)
		{
			math::Vector3 cameraPos = targetCamera->GetTransform()->GetPosition();
			std::function<void()> FrontToBackSortJob = [cameraPos, cameraIndex]()
			{
				std::vector<Renderer*>& renderers = dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer(cameraIndex);
								
				const size_t startRendererIndex = 0;
				const size_t rendererCount = renderers.size();

				for
				(
					size_t rendererIndex = startRendererIndex;
					rendererIndex < rendererCount;
					rendererIndex++
				)
				{
					renderers[rendererIndex]->CacheDistanceToCamera(cameraIndex, cameraPos);
				}

				D_START_PROFILING(SortRenderers, dooms::profiler::eProfileLayers::Rendering);
				dooms::graphics::SortFrontToBackSolver::SortRenderer(cameraIndex);
				D_END_PROFILING(SortRenderers);
			};

			IsFinishedSortingReferernceRenderers = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(FrontToBackSortJob);
		}

		D_ASSERT(IsValid(targetCamera));

		FrameBuffer::StaticBindBackFrameBuffer();
		GraphicsAPI::ClearBackFrameBufferColorBuffer(targetCamera->mClearColor[0], targetCamera->mClearColor[1], targetCamera->mClearColor[2], targetCamera->mClearColor[3]);
		GraphicsAPI::ClearBackFrameBufferDepthBuffer(GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);

		targetCamera->UpdateUniformBufferObject();

		targetCamera->mDeferredRenderingFrameBuffer.ClearFrameBuffer(targetCamera);
		targetCamera->mDeferredRenderingFrameBuffer.BindFrameBuffer();

		D_START_PROFILING(RenderObject, dooms::profiler::eProfileLayers::Rendering);
		//GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
		RenderObject(targetCamera, cameraIndex);
		D_END_PROFILING(RenderObject);

		FrameBuffer::StaticBindBackFrameBuffer();

		// 
		//Blit DepthBuffer To ScreenBuffer

		if (targetCamera->IsMainCamera() == true)
		{
			//Only Main Camera can draw to screen buffer
			mPIPManager.DrawPIPs();

			targetCamera->mDeferredRenderingFrameBuffer.BindGBufferTextures();
			mDeferredRenderingDrawer.DrawDeferredRenderingQuadDrawer();
			targetCamera->mDeferredRenderingFrameBuffer.UnBindGBufferTextures();

#ifdef DEBUG_DRAWER
			//�̰� ������ �������. �׳� ����� ����.

			DebugGraphics();
#endif
		}


		//Wait Multithread Sorting Renderer Front To Back  TO  JobSystem finished.
		D_START_PROFILING(WAIT_SORTING_RENDERER_JOB, dooms::profiler::eProfileLayers::Rendering);
		if (IsFinishedSortingReferernceRenderers.valid() == true)
		{
			IsFinishedSortingReferernceRenderers.wait();
		}
		D_END_PROFILING(WAIT_SORTING_RENDERER_JOB);

	}

	RendererComponentStaticIterator::GetSingleton()->ChangeWorkingIndexRenderers();

#ifdef DEBUG_DRAWER
	mDebugGraphics.SetIsVertexDataSendToGPUAtCurrentFrame(false);
#endif


	D_START_PROFILING(engineGUIServer_Render, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::Render();
	D_END_PROFILING(engineGUIServer_Render);

}

void dooms::graphics::Graphics_Server::ProfilingCullingSystem()
{
#if defined(PROFILING_CULLING) && defined(D_PROFILING)
	auto& profilingDatas = mCullingSystem->mEveryCullingProfiler.GetProfilingDatas();
	for (auto& data : profilingDatas)
	{
		const std::string cullingModuleTag{ data.first.data(), data.first.size() };
		dooms::profiling::profilingManager::AddProfilingData(cullingModuleTag.c_str(), (float)data.second.mElapsedTime);
	}
#endif
}

void dooms::graphics::Graphics_Server::PostRender()
{
	D_START_PROFILING(engineGUIServer_PostRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::PostRender();
	D_END_PROFILING(engineGUIServer_PostRender);

	D_START_PROFILING(ProfilingCullingSystem, dooms::profiler::eProfileLayers::Rendering);
	ProfilingCullingSystem();
	D_END_PROFILING(ProfilingCullingSystem);
}

void dooms::graphics::Graphics_Server::RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex)
{
	D_ASSERT(IsValid(targetCamera) == true);

	targetCamera->UpdateUniformBufferObject();


	D_START_PROFILING(DrawLoop, dooms::profiler::eProfileLayers::Rendering);
	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);

	UINT32 frontToBackOrder = 0;

	/*
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
	*/
	
	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(cameraIndex);
	for (Renderer* renderer : renderersInLayer)
	{
		if
			(
				IsValid(renderer) == true &&
				//renderer->GetOwnerEntityLayerIndex() == layerIndex && 
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
	D_END_PROFILING(DrawLoop);

	

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



