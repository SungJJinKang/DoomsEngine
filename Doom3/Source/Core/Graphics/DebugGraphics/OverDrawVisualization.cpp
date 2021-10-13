#include "OverDrawVisualization.h"


#ifdef DEBUG_DRAWER

#include "../Graphics_Setting.h"
#include "../Graphics_Server.h"
#include "Game/AssetManager/AssetManager.h"
#include <Asset/ShaderAsset.h>

#include "../Material/FixedMaterial.h"
#include "../Material/Material.h"
#include "../FrameBuffer/FrameBuffer.h"



class doom::graphics::OverDrawVisualization::OverDrawVisualizationPimpl
{
public:
	Material mOverDrawVisualizationObjectDrawMaterial;
	FrameBuffer mOverDrawVisualizationFrameBuffer;
	doom::graphics::PicktureInPickture* OverDrawVisualizationPIP = nullptr;
};

void doom::graphics::OverDrawVisualization::Initialize()
{
	mOverDrawVisualizationPimpl = std::make_unique<doom::graphics::OverDrawVisualization::OverDrawVisualizationPimpl>();
	doom::asset::ShaderAsset* overDrawVisualizationShader = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("OverDrawVisualizationShader.glsl");
	mOverDrawVisualizationPimpl->mOverDrawVisualizationObjectDrawMaterial = overDrawVisualizationShader->CreateMatrialWithThisShader();

	mOverDrawVisualizationPimpl->mOverDrawVisualizationFrameBuffer.GenerateBuffer(doom::graphics::Graphics_Setting::GetScreenWidth(), doom::graphics::Graphics_Setting::GetScreenHeight());
	mOverDrawVisualizationPimpl->mOverDrawVisualizationFrameBuffer.AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR);
	mOverDrawVisualizationPimpl->mOverDrawVisualizationFrameBuffer.AttachRenderBuffer(GraphicsAPI::eBufferBitType::DEPTH);

	bmIsInitialized = true;
}

void doom::graphics::OverDrawVisualization::ShowOverDrawVisualizationPIP(const bool isPIPDrawed)
{
	if(mOverDrawVisualizationPimpl)
	{
		if (mOverDrawVisualizationPimpl->OverDrawVisualizationPIP == nullptr)
		{
			mOverDrawVisualizationPimpl->OverDrawVisualizationPIP = doom::graphics::Graphics_Server::GetSingleton()->mPIPManager.AddNewPIP(
				math::Vector2(0.1f, 0.1f),
				math::Vector2(1.0f, 1.0f),
				mOverDrawVisualizationPimpl->mOverDrawVisualizationFrameBuffer.GetFrameBufferTexture(GraphicsAPI::eBufferBitType::COLOR, 0)
			);
		}

		if (mOverDrawVisualizationPimpl->OverDrawVisualizationPIP != nullptr)
		{
			mOverDrawVisualizationPimpl->OverDrawVisualizationPIP->bmIsDrawOnScreen = isPIPDrawed;
		}
	}
	
}

doom::graphics::OverDrawVisualization::OverDrawVisualization()
{
}

doom::graphics::OverDrawVisualization::~OverDrawVisualization()
{
}


void doom::graphics::OverDrawVisualization::SetOverDrawVisualizationRenderingState(const bool isSet)
{

	if (bmIsInitialized == false)
	{
		Initialize();
	}

	if (isSet == true)
	{
		GraphicsAPI::Enable(GraphicsAPI::eCapability::BLEND);
		GraphicsAPI::BlendFunc(GraphicsAPI::eSourceFactor::ONE, GraphicsAPI::eDestinationFactor::ONE);


		doom::graphics::FixedMaterial::SetFixedMaterial(&(mOverDrawVisualizationPimpl->mOverDrawVisualizationObjectDrawMaterial));
		mOverDrawVisualizationPimpl->mOverDrawVisualizationFrameBuffer.BindFrameBuffer();

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
		if (currentFixedMaterial == &(mOverDrawVisualizationPimpl->mOverDrawVisualizationObjectDrawMaterial))
		{
			doom::graphics::FixedMaterial::ClearFixedMaterial();
		}
		mOverDrawVisualizationPimpl->mOverDrawVisualizationFrameBuffer.UnBindFrameBuffer();
	}
}



#endif