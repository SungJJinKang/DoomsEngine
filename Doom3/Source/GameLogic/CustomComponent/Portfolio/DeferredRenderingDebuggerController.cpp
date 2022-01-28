#include "DeferredRenderingDebuggerController.h"

#include <Graphics/PictureInPicture/PicktureInPickture.h>

#include <Graphics/PictureInPicture/PIPManager.h>
#include "Rendering/Camera.h"

void dooms::DeferredRenderingDebuggerController::InitComponent()
{
	

	InitDeferredRenderingDebuggerPIP();

}

void dooms::DeferredRenderingDebuggerController::InitDeferredRenderingDebuggerPIP()
{
	if (dooms::Camera::GetMainCamera() != nullptr)
	{

		mDeferredRenderingDebuggerPIPs[0] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -1.0f, -1.0f }, { -0.6f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetColorTextureView(0, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		mDeferredRenderingDebuggerPIPs[1] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.6f, -1.0f }, { -0.2f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetColorTextureView(1, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		mDeferredRenderingDebuggerPIPs[2] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.2f, -1.0f }, { 0.2f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetColorTextureView(2, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		dooms::graphics::PicktureInPickture* depthTexturePIP = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ 0.2f, -1.0f }, { 0.6f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetDepthStencilTextureView(3, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		mDeferredRenderingDebuggerPIPs[3] = depthTexturePIP;

		if (depthTexturePIP != nullptr)
		{
			dooms::asset::ShaderAsset* const depthTextureShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("DepthBufferTextureShader.glsl");
			graphics::Material* const depthMaterial = dooms::CreateDObject<graphics::Material>(depthTextureShader);
			//depthMaterial->SetShaderAsset(depthTextureShader);
			depthTexturePIP->SetMaterial(depthMaterial);
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
