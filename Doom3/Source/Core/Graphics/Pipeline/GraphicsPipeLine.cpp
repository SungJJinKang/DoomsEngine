#include "GraphicsPipeLine.h"

#include "../Graphics_Server.h"
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Camera.h>
#include <Rendering/Renderer/Renderer.h>
#include "EngineGUI/engineGUIServer.h"
#include "EngineGUI/GUIModules/MaskedOcclusionCulliingDebugger.h"
#include "Graphics/GraphicsSetting.h"
#include "Graphics/Acceleration/SortFrontToBackSolver.h"
#include "ResourceManagement/JobSystem_cpp/JobSystem.h"

void dooms::graphics::GraphicsPipeLine::PreRenderRenderer()
{
	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(0);
	for (Renderer* renderer : renderersInLayer)
	{
		renderer->PreRender();
	}
}


dooms::graphics::GraphicsPipeLine::GraphicsPipeLine
(
	dooms::graphics::Graphics_Server& graphicsServer
)
	: mRenderingCullingManager(), mGraphicsServer(graphicsServer), mDeferredRenderingDrawer(), mRenderingDebugger()
{
}

void dooms::graphics::GraphicsPipeLine::Initialize()
{
	mDeferredRenderingDrawer.Initialize();
	mRenderingCullingManager.Initialize();
	dooms::ui::maskedOcclusionCulliingDebugger::Initilize(mRenderingCullingManager.mCullingSystem->mMaskedSWOcclusionCulling.get());
	mRenderingDebugger.Initialize();

}

void dooms::graphics::GraphicsPipeLine::LateInitialize()
{
	mRenderingDebugger.LateInitialize();
}

void dooms::graphics::GraphicsPipeLine::PreRender()
{

	D_START_PROFILING(PreRenderRenderer, dooms::profiler::eProfileLayers::Rendering);
	PreRenderRenderer();
	D_END_PROFILING(PreRenderRenderer);

	D_START_PROFILING(engineGUIServer_PreRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::PreRender();
	D_END_PROFILING(engineGUIServer_PreRender);

	mRenderingDebugger.PreRender();


	if (Camera::GetMainCamera()->GetIsCullJobEnabled() == true)
	{
		D_START_PROFILING(PreCullJob, dooms::profiler::eProfileLayers::Rendering);
		mRenderingCullingManager.PreCullJob();
		D_END_PROFILING(PreCullJob);
	}
}

void dooms::graphics::GraphicsPipeLine::Render()
{
	D_START_PROFILING(Update_Uniform_Buffer, dooms::profiler::eProfileLayers::Rendering);
	mGraphicsServer.mUniformBufferObjectManager.UpdateUniformObjects();
	D_END_PROFILING(Update_Uniform_Buffer);

	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();

	for (size_t cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];
		RenderCamera(targetCamera, cameraIndex);
	}

	RendererComponentStaticIterator::GetSingleton()->ChangeWorkingIndexRenderers();
	
	D_START_PROFILING(engineGUIServer_Render, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::Render();
	D_END_PROFILING(engineGUIServer_Render);

}

void dooms::graphics::GraphicsPipeLine::PostRender()
{
	D_START_PROFILING(engineGUIServer_PostRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::engineGUIServer::PostRender();
	D_END_PROFILING(engineGUIServer_PostRender);

	mRenderingDebugger.PostRender();
}


void dooms::graphics::GraphicsPipeLine::RenderObject(dooms::Camera* const targetCamera, const size_t cameraIndex)
{
	D_ASSERT(IsValid(targetCamera) == true);

	targetCamera->UpdateUniformBufferObject();

	D_START_PROFILING(DrawLoop, dooms::profiler::eProfileLayers::Rendering);
	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);
	
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
			if
			(
				targetCamera_IS_CULLED_flag_on == false ||
				renderer->GetIsCulled(targetCamera->CameraIndexInCullingSystem) == false
			)
			{
				renderer->Draw();
			}
		}
	}
	D_END_PROFILING(DrawLoop);
}

void dooms::graphics::GraphicsPipeLine::RenderCamera(dooms::Camera* const targetCamera, const size_t cameraIndex)
{
	D_ASSERT(IsValid(targetCamera));

	if (targetCamera->GetIsCullJobEnabled() == true)
	{
		mRenderingCullingManager.CameraCullJob(targetCamera); // do this first
	}

	std::future<void> IsFinishedSortingReferernceRenderers = PushFrontToBackSortJobToJobSystem(targetCamera, cameraIndex);
	
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
	
	if (targetCamera->IsMainCamera() == true)
	{
		//Only Main Camera can draw to screen buffer
		mGraphicsServer.mPIPManager.DrawPIPs();

		targetCamera->mDeferredRenderingFrameBuffer.BindGBufferTextures();
		mDeferredRenderingDrawer.DrawDeferredRenderingQuadDrawer();
		targetCamera->mDeferredRenderingFrameBuffer.UnBindGBufferTextures();


		mRenderingDebugger.Render();
	}


	//Wait Multithread Sorting Renderer Front To Back  TO  JobSystem finished.
	D_START_PROFILING(WAIT_SORTING_RENDERER_JOB, dooms::profiler::eProfileLayers::Rendering);
	if (IsFinishedSortingReferernceRenderers.valid() == true)
	{
		IsFinishedSortingReferernceRenderers.wait();
	}
	D_END_PROFILING(WAIT_SORTING_RENDERER_JOB);
}

std::future<void> dooms::graphics::GraphicsPipeLine::PushFrontToBackSortJobToJobSystem
(
	dooms::Camera* const targetCamera, const UINT32 cameraIndex
)
{
	std::future<void> future{};

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

		future = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(FrontToBackSortJob);
	}

	return future;
}


