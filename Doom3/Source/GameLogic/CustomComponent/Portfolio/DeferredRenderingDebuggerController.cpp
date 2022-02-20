#include "DeferredRenderingDebuggerController.h"

#include <PictureInPicture/PicktureInPickture.h>
#include <PictureInPicture/PIPManager.h>
#include "Rendering/Camera.h"
#include <Rendering/Pipeline/PipeLines/DeferredRendering/DeferredRenderingPipeLineCamera.h>

void dooms::DeferredRenderingDebuggerController::InitComponent()
{
	

	InitDeferredRenderingDebuggerPIP();

}

void dooms::DeferredRenderingDebuggerController::InitDeferredRenderingDebuggerPIP()
{
	if (dooms::Camera::GetMainCamera() != nullptr)
	{
		dooms::graphics::DeferredRenderingPipeLineCamera* const deferredRenderingPipeLineCamera = CastTo<graphics::DeferredRenderingPipeLineCamera*>(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera());
		D_ASSERT(IsValid(deferredRenderingPipeLineCamera));
		if(IsValid(deferredRenderingPipeLineCamera))
		{
			mDeferredRenderingDebuggerPIPs[0] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -1.0f, -1.0f }, { -0.6f, -0.6f }, deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.GetColorTextureView(0, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
			mDeferredRenderingDebuggerPIPs[1] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.6f, -1.0f }, { -0.2f, -0.6f }, deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.GetColorTextureView(1, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
			mDeferredRenderingDebuggerPIPs[2] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.2f, -1.0f }, { 0.2f, -0.6f }, deferredRenderingPipeLineCamera->mDeferredRenderingFrameBuffer.GetColorTextureView(2, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		}
	}

}

void dooms::DeferredRenderingDebuggerController::UpdateComponent()
{
}

void dooms::DeferredRenderingDebuggerController::OnEndOfFrame_Component()
{

}

void dooms::DeferredRenderingDebuggerController::SetPIPVisible(bool isVisible)
{
	for (auto pip : mDeferredRenderingDebuggerPIPs)
	{
		if (pip != nullptr)
		{
			pip->bmIsDrawOnScreen = isVisible;
		}

	}
}
