#include "DeferredRenderingPipeLine.h"

#include <Graphics/Graphics_Server.h>
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Camera.h>
#include <Rendering/Renderer/Renderer.h>
#include "EngineGUI/engineGUIServer.h"
#include "ResourceManagement/JobSystem_cpp/JobSystem.h"


dooms::graphics::DeferredRenderingPipeLine::DeferredRenderingPipeLine
(
	dooms::graphics::Graphics_Server& graphicsServer
)
	:
	dooms::graphics::DefaultGraphcisPipeLine(graphicsServer),
	mDeferredRenderingDrawer()
{
}

void dooms::graphics::DeferredRenderingPipeLine::Initialize()
{
	DefaultGraphcisPipeLine::Initialize();

	mDeferredRenderingDrawer.Initialize();

}

void dooms::graphics::DeferredRenderingPipeLine::LateInitialize()
{
	DefaultGraphcisPipeLine::LateInitialize();
}

void dooms::graphics::DeferredRenderingPipeLine::PreRender()
{
	DefaultGraphcisPipeLine::PreRender();

	D_START_PROFILING(PreRenderRenderer, dooms::profiler::eProfileLayers::Rendering);
	PreRenderRenderer();
	D_END_PROFILING(PreRenderRenderer);

	D_START_PROFILING(engineGUIServer_PreRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::EngineGUIServer::GetSingleton()->PreRender();
	D_END_PROFILING(engineGUIServer_PreRender);

	mRenderingDebugger.PreRender();


	if (Camera::GetMainCamera()->GetIsCullJobEnabled() == true)
	{
		D_START_PROFILING(PreCullJob, dooms::profiler::eProfileLayers::Rendering);
		mRenderingCullingManager.PreCullJob();
		D_END_PROFILING(PreCullJob);
	}
}

void dooms::graphics::DeferredRenderingPipeLine::Render()
{
	DefaultGraphcisPipeLine::Render();

	D_START_PROFILING(Update_Uniform_Buffer, dooms::profiler::eProfileLayers::Rendering);
	mGraphicsServer.mUniformBufferObjectManager.UpdateUniformObjects();
	D_END_PROFILING(Update_Uniform_Buffer);

	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();

	for (size_t cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];
		CameraRender(targetCamera, cameraIndex);
	}

	RendererComponentStaticIterator::GetSingleton()->ChangeWorkingIndexRenderers();
	
	D_START_PROFILING(engineGUIServer_Render, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::EngineGUIServer::GetSingleton()->Render();
	D_END_PROFILING(engineGUIServer_Render);

}

void dooms::graphics::DeferredRenderingPipeLine::PostRender()
{
	DefaultGraphcisPipeLine::PostRender();

	D_START_PROFILING(engineGUIServer_PostRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::EngineGUIServer::GetSingleton()->PostRender();
	D_END_PROFILING(engineGUIServer_PostRender);

	mRenderingDebugger.PostRender();

	D_START_PROFILING(SwapBuffer, dooms::profiler::eProfileLayers::Rendering);
	graphics::GraphicsAPI::SwapBuffer();
	D_END_PROFILING(SwapBuffer);

}

dooms::graphics::eGraphicsPipeLineType dooms::graphics::DeferredRenderingPipeLine::GetGraphicsPipeLineType() const
{
	return eGraphicsPipeLineType::DeferredRendering;
}


void dooms::graphics::DeferredRenderingPipeLine::RenderObjects(dooms::Camera* const targetCamera, const size_t cameraIndex)
{
	D_ASSERT(IsValid(targetCamera) == true);

	targetCamera->UpdateUniformBufferObject();

	D_START_PROFILING(DrawLoop, dooms::profiler::eProfileLayers::Rendering);
	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);
	
	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer();
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

void dooms::graphics::DeferredRenderingPipeLine::CameraRender(dooms::Camera* const targetCamera, const size_t cameraIndex)
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
	RenderObjects(targetCamera, cameraIndex);
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


