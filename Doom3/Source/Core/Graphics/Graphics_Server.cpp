#include "Graphics_Server.h"

#include <functional>

#include "../Game/GameCore.h"
#include "../Scene/Layer.h"
#include "../Game/AssetManager/AssetManager.h"

#include "GraphicsAPI.h"

#include "Buffer/UniformBufferObjectManager.h"

#include <Rendering/Renderer/Renderer.h>
#include "FrameBuffer/DefferedRenderingFrameBuffer.h"
#include <Rendering/Renderer/RendererStaticIterator.h>

#include "Rendering/Camera.h"

#include "Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"

#include "GraphicsAPIManager.h"
#include "Graphics_Setting.h"
#include "MainTimer.h"

#include "Acceleration/SortFrontToBackSolver.h"
#include "DebugGraphics/OverDrawVisualization.h"

//#define D_DEBUG_CPU_VENDOR_PROFILER

using namespace doom::graphics;


void Graphics_Server::Init()
{
	Graphics_Setting::LoadData();
	GraphicsAPIManager::Initialize();

	mCullingSystem = std::make_unique<culling::EveryCulling>(Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());

	return;
}

void doom::graphics::Graphics_Server::LateInit()
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
#ifdef DEBUG_DRAWER
	mDebugGraphics.Update();
	mRenderingDebugger.DrawRenderingBoundingBox();
#endif

	Renderder_UpdateComponent();

#ifdef DEBUG_DRAWER
	mRenderingDebugger.UpdateInputForPrintDrawCallCounter();
#endif

	//auto t_start = std::chrono::high_resolution_clock::now();
	
	D_START_PROFILING_IN_RELEASE(RENDER);
	Render();
	D_END_PROFILING_IN_RELEASE(RENDER);

	//Render();

	//auto t_end = std::chrono::high_resolution_clock::now();
	//FLOAT64 elapsed_time_ms = std::chrono::duration<FLOAT64, std::milli>(t_end - t_start).count();
	//doom::ui::PrintText("elapsed tick count : %lf", elapsed_time_ms);
}

void Graphics_Server::OnEndOfFrame()
{
	Renderder_OnEndOfFrameComponent();

#ifdef DEBUG_DRAWER
	mDebugGraphics.Reset();
#endif

	GraphicsAPIManager::SwapBuffer();
}

void doom::graphics::Graphics_Server::Renderder_InitComponent()
{
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetWorkingRendererInLayer(0, layerIndex);
		for (SIZE_T rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			//renderersInLayer[rendererIndex]->InitComponent_Internal();
			renderersInLayer[rendererIndex]->InitComponent();
		}
	}
}

void doom::graphics::Graphics_Server::Renderder_UpdateComponent()
{
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetWorkingRendererInLayer(0, layerIndex);
		for (SIZE_T rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			renderersInLayer[rendererIndex]->UpdateComponent_Internal();
			renderersInLayer[rendererIndex]->UpdateComponent();
		}
	}
}

void doom::graphics::Graphics_Server::Renderder_OnEndOfFrameComponent()
{
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetWorkingRendererInLayer(0, layerIndex);
		for (SIZE_T rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			renderersInLayer[rendererIndex]->OnEndOfFrame_Component_Internal();
			renderersInLayer[rendererIndex]->OnEndOfFrame_Component();
		}
	}
}



Graphics_Server::Graphics_Server()
{

}

Graphics_Server::~Graphics_Server()
{

}


void Graphics_Server::DoCullJob()
{
	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();

	UINT32 CullJobAvailiableCameraCount = 0;
	for (SIZE_T cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		doom::Camera* const camera = spawnedCameraList[cameraIndex];

		if (camera->GetIsCullJobEnabled() == true)
		{
			camera->CameraIndexInCullingSystem = CullJobAvailiableCameraCount;

			mCullingSystem->SetViewProjectionMatrix(CullJobAvailiableCameraCount, *reinterpret_cast<const culling::Mat4x4*>(&(camera->GetViewProjectionMatrix())));
			mCullingSystem->SetCameraPosition(
				CullJobAvailiableCameraCount,
				*reinterpret_cast<const culling::Vec3*>(&(camera->GetTransform()->GetPosition()))
			);

			CullJobAvailiableCameraCount++;
		}
	
	}

	if (CullJobAvailiableCameraCount > 0)
	{
		mCullingSystem->SetCameraCount(CullJobAvailiableCameraCount);

		D_START_PROFILING(mFrotbiteCullingSystem_ResetCullJobStat, doom::profiler::eProfileLayers::Rendering);
		mCullingSystem->ResetCullJobState();
		D_END_PROFILING(mFrotbiteCullingSystem_ResetCullJobStat);

		D_START_PROFILING(Push_Culling_Job_To_Linera_Culling_System, doom::profiler::eProfileLayers::Rendering);
		resource::JobSystem::GetSingleton()->PushBackJobToAllThreadWithNoSTDFuture(std::function<void()>(mCullingSystem->GetCullJobInLambda()));
		D_END_PROFILING(Push_Culling_Job_To_Linera_Culling_System);
	}
	
}

void doom::graphics::Graphics_Server::Render()
{
	DoCullJob(); // do this first
	//TODO : Think where put this, as early as good
	
	D_START_PROFILING(Update_Uniform_Buffer, doom::profiler::eProfileLayers::Rendering);
	mUniformBufferObjectManager.UpdateUniformObjects();
	D_END_PROFILING(Update_Uniform_Buffer);
	
	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();

	FrameBuffer::UnBindFrameBuffer();
	//Clear ScreenBuffer
	GraphicsAPI::DefaultClearColor(Graphics_Setting::DefaultClearColor);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	for (SIZE_T cameraIndex = 0 ; cameraIndex < spawnedCameraList.size() ; cameraIndex++)
	{
		doom::Camera* const targetCamera = spawnedCameraList[cameraIndex];
		targetCamera->UpdateUniformBufferObject();

		targetCamera->mDefferedRenderingFrameBuffer.ClearFrameBuffer();
		targetCamera->mDefferedRenderingFrameBuffer.BindFrameBuffer();
		
		D_START_PROFILING(RenderObject, doom::profiler::eProfileLayers::Rendering);
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
			//이거 느려도 상관없다. 그냥 여기다 두자.
			mDebugGraphics.BufferVertexDataToGPU();

		
			mDebugGraphics.Draw();
#endif
		}
		
	}

	RendererComponentStaticIterator::ChangeWorkingIndexRenderers();

#ifdef DEBUG_DRAWER
	mDebugGraphics.SetIsVertexDataSendToGPUAtCurrentFrame(false);
#endif


	
	
}

void doom::graphics::Graphics_Server::UpdateOverDrawVisualization(doom::Camera* const targetCamera, const SIZE_T cameraIndex)
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



void doom::graphics::Graphics_Server::RenderObject(doom::Camera* const targetCamera, const SIZE_T cameraIndex)
{
	targetCamera->UpdateUniformBufferObject();



	std::future<void> IsFinishedSortingReferernceRenderers;

	if (targetCamera->GetIsCullJobEnabled() == true)
	{
		D_START_PROFILING_IN_RELEASE(WAIT_CULLJOB);
		mCullingSystem->WaitToFinishCullJob(targetCamera->CameraIndexInCullingSystem); // Waiting time is almost zero
		//resource::JobSystem::GetSingleton()->SetMemoryBarrierOnAllSubThreads();
		D_END_PROFILING_IN_RELEASE(WAIT_CULLJOB);

		if (Graphics_Setting::IsSortObjectFrontToBack == true)
		{
			//Push Multithread Sorting Renderer Front To Back  TO  JobSystem.
			IsFinishedSortingReferernceRenderers = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(std::function<void()>(doom::graphics::SortFrontToBackSolver::GetSortRendererLambda(cameraIndex)));
		}
	}


	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(doom::eCameraFlag::IS_CULLED);
	for (UINT32 layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetWorkingRendererInLayer(cameraIndex, layerIndex);
		for (Renderer* renderer : renderersInLayer)
		{
			if (
				targetCamera_IS_CULLED_flag_on == false ||
				renderer->GetIsCulled(targetCamera->CameraIndexInCullingSystem) == false
				)
			{
				//renderer->ColliderUpdater<doom::physics::AABB3D>::GetWorldCollider()->DrawPhysicsDebugColor(eColor::Blue);
				renderer->Draw();
			}
		}
	}


	//Wait Multithread Sorting Renderer Front To Back  TO  JobSystem finished.
	if(IsFinishedSortingReferernceRenderers.valid() == true)
	{
		D_START_PROFILING_IN_RELEASE(WAIT_SORTING_RENDERER_JOB);
		IsFinishedSortingReferernceRenderers.wait();
		D_END_PROFILING_IN_RELEASE(WAIT_SORTING_RENDERER_JOB);
	}
	
}








void doom::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	mCurrentRenderingMode = renderingMode;
	if (mCurrentRenderingMode == eRenderingMode::DeferredRendering)
	{
		mDeferredRenderingDrawer.Initialize();
	}
}



