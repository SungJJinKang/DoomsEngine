#include "DeferredRenderingDebuggerController.h"

#include <Graphics/PictureInPicture/PicktureInPickture.h>
#include "Rendering/Camera.h"

void doom::DeferredRenderingDebuggerController::InitComponent()
{
	

	InitDeferredRenderingDebuggerPIP();

}

void doom::DeferredRenderingDebuggerController::InitDeferredRenderingDebuggerPIP()
{
	if (doom::Camera::GetMainCamera() != nullptr)
	{

		mDeferredRenderingDebuggerPIPs[0] = doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ -1.0f, -1.0f }, { -0.6f, -0.6f }, doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 0));
		mDeferredRenderingDebuggerPIPs[1] = doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.6f, -1.0f }, { -0.2f, -0.6f }, doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 1));
		mDeferredRenderingDebuggerPIPs[2] = doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.2f, -1.0f }, { 0.2f, -0.6f }, doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 2));
		doom::graphics::PicktureInPickture* depthTexturePIP = doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ 0.2f, -1.0f }, { 0.6f, -0.6f }, doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::DEPTH, 0));
		mDeferredRenderingDebuggerPIPs[3] = depthTexturePIP;

		if (depthTexturePIP != nullptr)
		{
			doom::asset::ShaderAsset* const depthTextureShader = doom::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("DepthBufferTextureShader.glsl");
			graphics::Material* const depthMaterial = doom::CreateDObject<graphics::Material>(depthTextureShader);
			//depthMaterial->SetShaderAsset(depthTextureShader);
			depthTexturePIP->SetMaterial(depthMaterial);
		}

	}

}

void doom::DeferredRenderingDebuggerController::UpdateComponent()
{

	if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F3))
	{
		for (auto pip : mDeferredRenderingDebuggerPIPs)
		{
			if (pip != nullptr)
			{
				pip->bmIsDrawOnScreen = !(pip->bmIsDrawOnScreen);
			}
		
		}
	}

}

void doom::DeferredRenderingDebuggerController::OnEndOfFrame_Component()
{

}
