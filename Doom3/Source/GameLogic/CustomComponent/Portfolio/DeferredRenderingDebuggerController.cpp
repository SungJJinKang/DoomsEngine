#include "DeferredRenderingDebuggerController.h"

#include <Rendering/PictureInPicture/PicktureInPickture.h>
#include <Rendering/PictureInPicture/PIPManager.h>
#include "Rendering/Camera.h"

void dooms::DeferredRenderingDebuggerController::InitComponent()
{
	

	InitDeferredRenderingDebuggerPIP();

}

void dooms::DeferredRenderingDebuggerController::InitDeferredRenderingDebuggerPIP()
{
	if (dooms::Camera::GetMainCamera() != nullptr)
	{

		mDeferredRenderingDebuggerPIPs[0] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -1.0f, -1.0f }, { -0.6f, -0.6f }, dooms::Camera::GetMainCamera()->mDeferredRenderingFrameBuffer.GetColorTextureView(0, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		mDeferredRenderingDebuggerPIPs[1] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.6f, -1.0f }, { -0.2f, -0.6f }, dooms::Camera::GetMainCamera()->mDeferredRenderingFrameBuffer.GetColorTextureView(1, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		mDeferredRenderingDebuggerPIPs[2] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.2f, -1.0f }, { 0.2f, -0.6f }, dooms::Camera::GetMainCamera()->mDeferredRenderingFrameBuffer.GetColorTextureView(2, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));

		// TODO : Support Depth Buffer PIP for D3D11 : https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil#reading-the-depth-stencil-buffer-as-a-texture
		/*
		dooms::graphics::PicktureInPickture* depthTexturePIP = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ 0.2f, -1.0f }, { 0.6f, -0.6f }, dooms::Camera::GetMainCamera()->mDeferredRenderingFrameBuffer.GetDepthStencilTextureView(3, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
		mDeferredRenderingDebuggerPIPs[3] = depthTexturePIP;

		if (depthTexturePIP != nullptr)
		{
			dooms::asset::ShaderAsset* const depthTextureShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("DepthBufferTextureShader.glsl");
			graphics::Material* const depthMaterial = dooms::CreateDObject<graphics::Material>(depthTextureShader);
			//depthMaterial->SetShaderAsset(depthTextureShader);
			depthTexturePIP->SetMaterial(depthMaterial);
		}
		*/

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
