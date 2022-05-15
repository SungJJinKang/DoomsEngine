#include "DeferredRenderingPipeLine.h"

#include <Rendering/Graphics_Server.h>
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"
#include <Rendering/Camera.h>
#include <Rendering/Renderer/Renderer.h>
#include "ResourceManagement/JobSystem_cpp/JobSystem.h"
#include "DeferredRenderingPipeLineCamera.h"

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

	
}

void dooms::graphics::DeferredRenderingPipeLine::Render()
{
	DefaultGraphcisPipeLine::Render();

	
	
	

}

void dooms::graphics::DeferredRenderingPipeLine::PostRender()
{
	DefaultGraphcisPipeLine::PostRender();

}

dooms::graphics::eGraphicsPipeLineType dooms::graphics::DeferredRenderingPipeLine::GetGraphicsPipeLineType() const
{
	return eGraphicsPipeLineType::DeferredRendering;
}

dooms::graphics::GraphicsPipeLineCamera* dooms::graphics::DeferredRenderingPipeLine::CreateGraphicsPipeLineCamera() const
{
	return dooms::CreateDObject<DeferredRenderingPipeLineCamera>();
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

	dooms::graphics::DeferredRenderingPipeLineCamera* const deferredRenderingPipeLineCamera = CastTo<graphics::DeferredRenderingPipeLineCamera*>(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera());
	D_ASSERT(IsValid(deferredRenderingPipeLineCamera));
	if (IsValid(deferredRenderingPipeLineCamera))
	{
		deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.ClearFrameBuffer(targetCamera);
		deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.BindFrameBuffer();
	}

	targetCamera->UpdateUniformBufferObject();


	if(dooms::graphics::graphicsAPISetting::DepthPrePassType == dooms::graphics::eDepthPrePassType::FullOpaque)
	{
		D_START_PROFILING(RenderObject_DepthPrePass, dooms::profiler::eProfileLayers::Rendering);

		dooms::graphics::FixedMaterial::GetSingleton()->SetFixedMaterial(GetDepthOnlyMaterial());
		GraphicsAPI::SetIsDepthTestEnabled(true);
		GraphicsAPI::SetDepthMask(true);
		GraphicsAPI::SetDepthFunc(GraphicsAPI::eTestFuncType::LESS);
		DrawRenderers(targetCamera, cameraIndex);
		dooms::graphics::FixedMaterial::GetSingleton()->SetFixedMaterial(nullptr);

		D_END_PROFILING(RenderObject_DepthPrePass);
	}
	

	{
		D_START_PROFILING(RenderObject, dooms::profiler::eProfileLayers::Rendering);
		GraphicsAPI::SetIsDepthTestEnabled(true);
		GraphicsAPI::SetDepthMask(true);
		GraphicsAPI::SetDepthFunc(GraphicsAPI::eTestFuncType::LEQUAL);
		DrawBatchedRenderers();
		DrawRenderers(targetCamera, cameraIndex);
		D_END_PROFILING(RenderObject);
	}
	
	FrameBuffer::StaticBindBackFrameBuffer();
	
	if (targetCamera->IsMainCamera() == true)
	{
		//Only Main Camera can draw to screen buffer
		mGraphicsServer.mPIPManager.DrawPIPs();

		dooms::graphics::DeferredRenderingPipeLineCamera* const deferredRenderingPipeLineCamera = CastTo<graphics::DeferredRenderingPipeLineCamera*>(targetCamera->GetGraphicsPipeLineCamera());
		D_ASSERT(IsValid(deferredRenderingPipeLineCamera));
		if (IsValid(deferredRenderingPipeLineCamera))
		{
			deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.BindGBufferTextures();
			mDeferredRenderingDrawer.DrawDeferredRenderingQuadDrawer();
			deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.UnBindGBufferTextures();
		}

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


