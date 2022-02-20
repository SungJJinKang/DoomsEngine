#include "OverDrawVisualization.h"

#include <Graphics/Graphics_Core.h>

#include <Graphics/GraphicsAPI/graphicsAPISetting.h>
#include <Rendering/Graphics_Server.h>
#include <Asset/AssetManager/AssetManager.h>
#include <Asset/ShaderAsset.h>
#include <Rendering/Material/FixedMaterial.h>
#include <Rendering/Material/Material.h>
#include <Rendering/FrameBuffer/FrameBuffer.h>



void dooms::graphics::OverDrawVisualization::ShowOverDrawVisualizationPIP(const bool isPIPDrawed)
{
	if (OverDrawVisualizationPIP != nullptr)
	{
		OverDrawVisualizationPIP->bmIsDrawOnScreen = isPIPDrawed;
	}
	
}

void dooms::graphics::OverDrawVisualization::Initialize()
{
	dooms::asset::ShaderAsset* overDrawVisualizationShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<dooms::asset::eAssetType::SHADER>("OverDrawVisualizationShader.glsl");
	mOverDrawVisualizationObjectDrawMaterial = overDrawVisualizationShader->CreateMatrialWithThisShaderAsset();
	mOverDrawVisualizationObjectDrawMaterial->AddToRootObjectList();
	D_ASSERT(IsValid(mOverDrawVisualizationObjectDrawMaterial));

	mOverDrawVisualizationFrameBuffer = dooms::CreateDObject<dooms::graphics::FrameBuffer>();
	mOverDrawVisualizationFrameBuffer->AttachColorTextureToFrameBuffer(0, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	mOverDrawVisualizationFrameBuffer->AttachDepthTextureToFrameBuffer(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	mOverDrawVisualizationFrameBuffer->AddToRootObjectList();

	OverDrawVisualizationPIP = dooms::graphics::Graphics_Server::GetSingleton()->mPIPManager.AddNewPIP(
		math::Vector2(-1.0f, -1.0f),
		math::Vector2(1.0f, 1.0f),
		mOverDrawVisualizationFrameBuffer->GetColorTextureView(0, GraphicsAPI::PIXEL_SHADER)
	);
	OverDrawVisualizationPIP->AddToRootObjectList();
	OverDrawVisualizationPIP->bmIsDrawOnScreen = false;

	bmIsOverDrawVisualizationInitialized = true;
}

void dooms::graphics::OverDrawVisualization::PreRender()
{
}

void dooms::graphics::OverDrawVisualization::Render()
{
}

void dooms::graphics::OverDrawVisualization::PostRender()
{
}

const char* dooms::graphics::OverDrawVisualization::GetRenderingDebuggerModuleName()
{
	return "OverDrawVisualization";
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

		D_ASSERT(IsValid(mOverDrawVisualizationObjectDrawMaterial));
		dooms::graphics::FixedMaterial::GetSingleton()->SetFixedMaterial(mOverDrawVisualizationObjectDrawMaterial);

		mOverDrawVisualizationFrameBuffer->ClearColorTexture(0, 0.0f, 0.0f, 0.0f, 1.0f);
		mOverDrawVisualizationFrameBuffer->ClrearDepthTexture(GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);
	}
	else
	{
		GraphicsAPI::SetIsBlendEnabled(graphicsAPISetting::DefaultIsBlendOn);
		GraphicsAPI::SetBlendFactor(graphics::graphicsAPISetting::DefaultBlendSourceFactor, graphics::graphicsAPISetting::DefaultBlendDestinationFactor);

		

		const dooms::graphics::Material* const currentFixedMaterial = dooms::graphics::FixedMaterial::GetSingleton()->GetFixedMaterial();
		D_ASSERT(IsValid(mOverDrawVisualizationObjectDrawMaterial));
		if (currentFixedMaterial == mOverDrawVisualizationObjectDrawMaterial)
		{
			dooms::graphics::FixedMaterial::GetSingleton()->ClearFixedMaterial();
		}
		FrameBuffer::StaticBindBackFrameBuffer();
	}
}


