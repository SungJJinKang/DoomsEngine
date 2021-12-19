#include "Graphics_Server.h"

#include <functional>

#include "../Game/GameCore.h"
#include "../Scene/Layer.h"
#include "../Game/AssetManager/AssetManager.h"

#include "GraphicsAPI.h"

#include "Buffer/UniformBufferObjectManager.h"

#include <Rendering/Renderer/Renderer.h>
#include <Rendering/Light/Light.h>
#include "FrameBuffer/DefferedRenderingFrameBuffer.h"
#include <Rendering/Renderer/RendererStaticIterator.h>

#include "Rendering/Camera.h"

#include "Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"

#include "graphicsAPIManager.h"
#include "Graphics_Setting.h"
#include "MainTimer.h"

#include "Acceleration/SortFrontToBackSolver.h"
#include "DebugGraphics/OverDrawVisualization.h"
#include "DebugGraphics/maskedOcclusionCullingTester.h"
#include "Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.h"

//#define D_DEBUG_CPU_VENDOR_PROFILER

using namespace dooms::graphics;

void Graphics_Server::Init()
{
	Graphics_Setting::LoadData();
	graphicsAPIManager::Initialize();

	mCullingSystem = std::make_unique<culling::EveryCulling>(Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	mCullingSystem->mMaskedSWOcclusionCulling->mSolveMeshRoleStage.mOccluderViewSpaceBoundingSphereRadius = ConfigData::GetSingleton()->GetConfigData().GetValue<FLOAT32>("Graphics", "MASKED_OC_OCCLUDER_VIEW_SPACE_BOUNDING_SPHERE_RADIUS");

	return;
}

void dooms::graphics::Graphics_Server::LateInit()
{
#ifdef DEBUG_DRAWER
	mDebugGraphics.Init();
#endif 

	SetRenderingMode(Graphics_Server::eRenderingMode::DeferredRendering);


	//mQueryOcclusionCulling.InitQueryOcclusionCulling();
	//mCullDistance.Initialize();
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
}

void Graphics_Server::OnEndOfFrame()
{
#ifdef DEBUG_DRAWER
	mDebugGraphics.Reset();
#endif

	graphicsAPIManager::SwapBuffer();
}

Graphics_Server::Graphics_Server()
{

}

Graphics_Server::~Graphics_Server()
{
	graphicsAPIManager::DeInitialize();
}

void Graphics_Server::PreCullJob()
{
	mCullingCameraCount = 0;

	mCullingSystem->SetThreadCount(resource::JobSystem::GetSingleton()->GetSubThreadCount());

	D_START_PROFILING(mFrotbiteCullingSystem_ResetCullJobStat, dooms::profiler::eProfileLayers::Rendering);
	mCullingSystem->ResetCullJobState();
	D_END_PROFILING(mFrotbiteCullingSystem_ResetCullJobStat);

}


void Graphics_Server::CameraCullJob(dooms::Camera* const camera)
{
	if (camera->GetIsCullJobEnabled() == true)
	{
		culling::EveryCulling::SettingParameters cullingSettingParameters;
		cullingSettingParameters.mViewProjectionMatrix = *reinterpret_cast<const culling::Mat4x4*>(&(camera->GetViewProjectionMatrix()));
		cullingSettingParameters.mFieldOfViewInDegree = camera->GetFieldOfViewInDegree();
		cullingSettingParameters.mCameraFarPlaneDistance = camera->GetClippingPlaneFar();
		cullingSettingParameters.mCameraNearPlaneDistance = camera->GetClippingPlaneNear();
		cullingSettingParameters.mCameraWorldPosition = *reinterpret_cast<const culling::Vec3*>(&(camera->GetTransform()->GetPosition()));

		mCullingSystem->Configure(camera->CameraIndexInCullingSystem, cullingSettingParameters);
		
		std::atomic_thread_fence(std::memory_order_seq_cst);

		D_START_PROFILING(Push_Culling_Job_To_Linera_Culling_System, dooms::profiler::eProfileLayers::Rendering);
		resource::JobSystem::GetSingleton()->PushBackJobToAllThreadWithNoSTDFuture(std::function<void()>(mCullingSystem->GetCullJobInLambda(camera->CameraIndexInCullingSystem)));
		D_END_PROFILING(Push_Culling_Job_To_Linera_Culling_System);
	}
	
	

}

void Graphics_Server::DebugGraphics()
{
	/*
	//mCullingSystem->
	for(auto entityBlock : mCullingSystem->GetActiveEntityBlockList())
	{
		for(size_t entityIndex = 0 ; entityIndex < entityBlock->mCurrentEntityCount ; entityIndex++)
		{
			if
			(
				entityBlock->GetIsCulled(entityIndex, 0) == false &&
				entityBlock->GetIsOccluder(entityIndex, 0) == true
			)
			{
				mDebugGraphics.DebugDraw3DSphere
				(
					*(math::Vector3*)(&(entityBlock->mPositionAndBoundingSpheres[entityIndex].Position)),
					entityBlock->mPositionAndBoundingSpheres[entityIndex].BoundingSphereRadius + 0.3f,
					eColor::Red
				);
			}
		}
	}
	*/
	const UINT32 tileCount = mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer.GetTileCount();
	const culling::Tile* const tiles = mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer.GetTiles();
	for(size_t i = 0 ; i < tileCount ; i++)
	{
		const size_t triangleCount = tiles[i].mBinnedTriangles.mCurrentTriangleCount;
		for (size_t tri = 0; tri < triangleCount; tri++)
		{
			mDebugGraphics.DebugDraw2DTriangleScreenSpace
			(
				*(const math::Vector3*)(tiles[i].mBinnedTriangles.mTriangleList[tri].Points + 0),
				*(const math::Vector3*)(tiles[i].mBinnedTriangles.mTriangleList[tri].Points + 1),
				*(const math::Vector3*)(tiles[i].mBinnedTriangles.mTriangleList[tri].Points + 2),
				eColor::Green
			);
			
		}
	}

	mDebugGraphics.BufferVertexDataToGPU();
	mDebugGraphics.Draw();

}

void Graphics_Server::PreRender()
{
	dooms::ui::engineGUIServer::PreRender();
	if(Camera::GetMainCamera()->GetIsCullJobEnabled() == true)
	{
		PreCullJob();
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
			targetCamera->CameraIndexInCullingSystem = mCullingCameraCount;

			mCullingCameraCount++;
			mCullingSystem->SetCameraCount(mCullingCameraCount);

			CameraCullJob(targetCamera); // do this first
		}
		


		D_ASSERT(IsValid(targetCamera));

		GraphicsAPI::ClearColor(targetCamera->mClearColor);
		GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

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


	dooms::ui::engineGUIServer::Render();

	
}

void Graphics_Server::PostRender()
{
	dooms::ui::engineGUIServer::PostRender();

}

void dooms::graphics::Graphics_Server::UpdateOverDrawVisualization(dooms::Camera* const targetCamera, const size_t cameraIndex)
{

#ifdef DEBUG_DRAWER
	OverDrawVisualization::ShowOverDrawVisualizationPIP(Graphics_Setting::IsOverDrawVisualizationEnabled);
	if (Graphics_Setting::IsOverDrawVisualizationEnabled == true)
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

	if (targetCamera->GetIsCullJobEnabled() == true)
	{
		D_START_PROFILING(WAIT_CULLJOB, dooms::profiler::eProfileLayers::Rendering);
		mCullingSystem->WaitToFinishCullJob(targetCamera->CameraIndexInCullingSystem); // Waiting time is almost zero
		//resource::JobSystem::GetSingleton()->SetMemoryBarrierOnAllSubThreads();
		D_END_PROFILING(WAIT_CULLJOB);

		
	}

	if (Graphics_Setting::IsSortObjectFrontToBack == true)
	{
		math::Vector3 cameraPos = targetCamera->GetTransform()->GetPosition();
		for(size_t layerIndex = 0 ; layerIndex < MAX_LAYER_COUNT ; layerIndex++)
		{
			for(Renderer* renderer : dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer(cameraIndex, layerIndex))
			{
				renderer->CacheDistanceToCamera(cameraIndex, cameraPos);
			}
		}

		//Push Multithread Sorting Renderer Front To Back  TO  JobSystem.
		IsFinishedSortingReferernceRenderers = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(std::function<void()>(dooms::graphics::SortFrontToBackSolver::GetSortRendererLambda(cameraIndex)));
	}

	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetWorkingRendererInLayer(cameraIndex, layerIndex);
		for (Renderer* renderer : renderersInLayer)
		{
			if(IsValid(renderer) == true)
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


	//Wait Multithread Sorting Renderer Front To Back  TO  JobSystem finished.
	if(IsFinishedSortingReferernceRenderers.valid() == true)
	{
		D_START_PROFILING(WAIT_SORTING_RENDERER_JOB, dooms::profiler::eProfileLayers::Rendering);
		IsFinishedSortingReferernceRenderers.wait();
		D_END_PROFILING(WAIT_SORTING_RENDERER_JOB);
	}
	
}



void dooms::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	mCurrentRenderingMode = renderingMode;
	if (mCurrentRenderingMode == eRenderingMode::DeferredRendering)
	{
		mDeferredRenderingDrawer.Initialize();
	}
}



