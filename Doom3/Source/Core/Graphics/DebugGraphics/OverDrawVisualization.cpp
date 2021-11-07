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


namespace dooms
{
	namespace graphics
	{
		namespace OverDrawVisualization
		{
			extern bool bmIsOverDrawVisualizationInitialized{false};
			extern dooms::graphics::Material mOverDrawVisualizationObjectDrawMaterial{};
			extern dooms::graphics::FrameBuffer mOverDrawVisualizationFrameBuffer{};
			extern dooms::graphics::PicktureInPickture* OverDrawVisualizationPIP{nullptr};

			extern void Initialize()
			{
				dooms::asset::ShaderAsset* overDrawVisualizationShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<dooms::asset::eAssetType::SHADER>("OverDrawVisualizationShader.glsl");
				mOverDrawVisualizationObjectDrawMaterial = overDrawVisualizationShader->CreateMatrialWithThisShader();

				mOverDrawVisualizationFrameBuffer.GenerateBuffer(dooms::graphics::Graphics_Setting::GetScreenWidth(), dooms::graphics::Graphics_Setting::GetScreenHeight());
				mOverDrawVisualizationFrameBuffer.AttachTextureBuffer(dooms::graphics::GraphicsAPI::eBufferBitType::COLOR);
				mOverDrawVisualizationFrameBuffer.AttachRenderBuffer(dooms::graphics::GraphicsAPI::eBufferBitType::DEPTH);
				
				OverDrawVisualizationPIP = dooms::graphics::Graphics_Server::GetSingleton()->mPIPManager.AddNewPIP(
					math::Vector2(0.1f, 0.1f),
					math::Vector2(1.0f, 1.0f),
					mOverDrawVisualizationFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::COLOR, 0)
				);

				bmIsOverDrawVisualizationInitialized = true;
			}
		}
	}
}

void dooms::graphics::OverDrawVisualization::ShowOverDrawVisualizationPIP(const bool isPIPDrawed)
{
	if (OverDrawVisualizationPIP != nullptr)
	{
		OverDrawVisualizationPIP->bmIsDrawOnScreen = isPIPDrawed;
	}
	
}


void dooms::graphics::OverDrawVisualization::SetOverDrawVisualizationRenderingState(const bool isSet)
{
	if (bmIsOverDrawVisualizationInitialized == false)
	{
		Initialize();
	}

	if (isSet == true)
	{
		GraphicsAPI::Enable(GraphicsAPI::eCapability::BLEND);
		GraphicsAPI::BlendFunc(GraphicsAPI::eSourceFactor::ONE, GraphicsAPI::eDestinationFactor::ONE);


		dooms::graphics::FixedMaterial::SetFixedMaterial(&(mOverDrawVisualizationObjectDrawMaterial));
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
		
		

		const dooms::graphics::Material* const currentFixedMaterial = dooms::graphics::FixedMaterial::GetFixedMaterial();
		if (currentFixedMaterial == &(mOverDrawVisualizationObjectDrawMaterial))
		{
			dooms::graphics::FixedMaterial::ClearFixedMaterial();
		}
		mOverDrawVisualizationFrameBuffer.UnBindFrameBuffer();
	}
}



#endif