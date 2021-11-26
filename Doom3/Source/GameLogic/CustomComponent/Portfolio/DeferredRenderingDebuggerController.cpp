#include "DeferredRenderingDebuggerController.h"

#include <Graphics/PictureInPicture/PicktureInPickture.h>
#include "Rendering/Camera.h"

void dooms::DeferredRenderingDebuggerController::InitComponent()
{
	

	InitDeferredRenderingDebuggerPIP();

}

void dooms::DeferredRenderingDebuggerController::InitDeferredRenderingDebuggerPIP()
{
	if (dooms::Camera::GetMainCamera() != nullptr)
	{

		mDeferredRenderingDebuggerPIPs[0] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -1.0f, -1.0f }, { -0.6f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::COLOR, 0));
		mDeferredRenderingDebuggerPIPs[1] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.6f, -1.0f }, { -0.2f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::COLOR, 1));
		mDeferredRenderingDebuggerPIPs[2] = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.2f, -1.0f }, { 0.2f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::COLOR, 2));
		dooms::graphics::PicktureInPickture* depthTexturePIP = dooms::graphics::PIPManager::GetSingleton()->AddNewPIP({ 0.2f, -1.0f }, { 0.6f, -0.6f }, dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::DEPTH, 0));
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
