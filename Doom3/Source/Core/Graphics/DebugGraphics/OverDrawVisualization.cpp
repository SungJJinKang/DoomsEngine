#include "OverDrawVisualization.h"

#include <Graphics/Graphics_Core.h>

#ifdef DEBUG_DRAWER

#include "../GraphicsAPI/graphicsAPISetting.h"
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

				mOverDrawVisualizationFrameBuffer.AttachColorTextureToFrameBuffer(0, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
				mOverDrawVisualizationFrameBuffer.AttachDepthTextureToFrameBuffer(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
				
				OverDrawVisualizationPIP = dooms::graphics::Graphics_Server::GetSingleton()->mPIPManager.AddNewPIP(
					math::Vector2(-1.0f, -1.0f),
					math::Vector2(1.0f, 1.0f),
					mOverDrawVisualizationFrameBuffer.GetDepthTextureView(0, GraphicsAPI::PIXEL_SHADER)
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
		GraphicsAPI::SetIsBlendEnabled(true);
		GraphicsAPI::SetBlendFactor(GraphicsAPI::eBlendFactor::ONE, GraphicsAPI::eBlendFactor::ONE);


		dooms::graphics::FixedMaterial::SetFixedMaterial(&(mOverDrawVisualizationObjectDrawMaterial));

		mOverDrawVisualizationFrameBuffer.ClearColorTexture(0, 0.0f, 0.0f, 0.0f, 1.0f);
		mOverDrawVisualizationFrameBuffer.ClrearDepthTexture(GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);
	}
	else
	{
		if (graphicsAPISetting::DefaultIsBlendOn == true)
		{
			GraphicsAPI::SetIsBlendEnabled(true);
			GraphicsAPI::SetBlendFactor(graphics::graphicsAPISetting::DefaultBlendSourceFactor, graphics::graphicsAPISetting::DefaultBlendDestinationFactor);
		}
		else
		{
			GraphicsAPI::SetIsBlendEnabled(false);
		}
		
		

		const dooms::graphics::Material* const currentFixedMaterial = dooms::graphics::FixedMaterial::GetFixedMaterial();
		if (currentFixedMaterial == &(mOverDrawVisualizationObjectDrawMaterial))
		{
			dooms::graphics::FixedMaterial::ClearFixedMaterial();
		}
		FrameBuffer::StaticBindBackFrameBuffer();
	}
}



#endif