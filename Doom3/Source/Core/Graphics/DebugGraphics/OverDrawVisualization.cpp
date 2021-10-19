#include "OverDrawVisualization.h"

#include <Graphics/Graphics_Core.h>

#ifdef DEBUG_DRAWER

#include "../Graphics_Setting.h"
#include "../Graphics_Server.h"
#include "Game/AssetManager/AssetManager.h"
#include <Asset/ShaderAsset.h>

#include "../Material/FixedMaterial.h"
#include "../Material/Material.h"
#include "../FrameBuffer/FrameBuffer.h"


namespace doom
{
	namespace graphics
	{
		namespace OverDrawVisualization
		{
			extern bool bmIsOverDrawVisualizationInitialized{false};
			extern doom::graphics::Material mOverDrawVisualizationObjectDrawMaterial{};
			extern doom::graphics::FrameBuffer mOverDrawVisualizationFrameBuffer{};
			extern doom::graphics::PicktureInPickture* OverDrawVisualizationPIP{nullptr};

			extern void Initialize()
			{
				doom::asset::ShaderAsset* overDrawVisualizationShader = doom::assetimporter::AssetManager::GetSingleton()->GetAsset<doom::asset::eAssetType::SHADER>("OverDrawVisualizationShader.glsl");
				mOverDrawVisualizationObjectDrawMaterial = overDrawVisualizationShader->CreateMatrialWithThisShader();

				mOverDrawVisualizationFrameBuffer.GenerateBuffer(doom::graphics::Graphics_Setting::GetScreenWidth(), doom::graphics::Graphics_Setting::GetScreenHeight());
				mOverDrawVisualizationFrameBuffer.AttachTextureBuffer(doom::graphics::GraphicsAPI::eBufferBitType::COLOR);
				mOverDrawVisualizationFrameBuffer.AttachRenderBuffer(doom::graphics::GraphicsAPI::eBufferBitType::DEPTH);
				
				OverDrawVisualizationPIP = doom::graphics::Graphics_Server::GetSingleton()->mPIPManager.AddNewPIP(
					math::Vector2(0.1f, 0.1f),
					math::Vector2(1.0f, 1.0f),
					mOverDrawVisualizationFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 0)
				);

				bmIsOverDrawVisualizationInitialized = true;
			}
		}
	}
}

void doom::graphics::OverDrawVisualization::ShowOverDrawVisualizationPIP(const bool isPIPDrawed)
{
	if (OverDrawVisualizationPIP != nullptr)
	{
		OverDrawVisualizationPIP->bmIsDrawOnScreen = isPIPDrawed;
	}
	
}


void doom::graphics::OverDrawVisualization::SetOverDrawVisualizationRenderingState(const bool isSet)
{
	if (bmIsOverDrawVisualizationInitialized == false)
	{
		Initialize();
	}

	if (isSet == true)
	{
		GraphicsAPI::Enable(GraphicsAPI::eCapability::BLEND);
		GraphicsAPI::BlendFunc(GraphicsAPI::eSourceFactor::ONE, GraphicsAPI::eDestinationFactor::ONE);


		doom::graphics::FixedMaterial::SetFixedMaterial(&(mOverDrawVisualizationObjectDrawMaterial));
		mOverDrawVisualizationFrameBuffer.BindFrameBuffer();

		GraphicsAPI::DefaultClearColor(math::Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);
	}
	else
	{
		if (Graphics_Setting::DefaultIsBlendOn == true)
		{
			GraphicsAPI::Enable(GraphicsAPI::eCapability::BLEND);
			GraphicsAPI::BlendFunc(Graphics_Setting::DefaultBlendSourceFactor, Graphics_Setting::DefaultBlendDestinationFactor);
		}
		else
		{
			GraphicsAPI::Disable(GraphicsAPI::eCapability::BLEND);
		}
		
		

		const doom::graphics::Material* const currentFixedMaterial = doom::graphics::FixedMaterial::GetFixedMaterial();
		if (currentFixedMaterial == &(mOverDrawVisualizationObjectDrawMaterial))
		{
			doom::graphics::FixedMaterial::ClearFixedMaterial();
		}
		mOverDrawVisualizationFrameBuffer.UnBindFrameBuffer();
	}
}



#endif