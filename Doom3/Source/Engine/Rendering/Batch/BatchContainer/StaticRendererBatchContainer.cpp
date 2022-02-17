#include "StaticRendererBatchContainer.h"

#include <Rendering/Renderer/MeshRenderer.h>
#include "meshBatchCreater.h"
#include <Asset/ShaderAsset.h>
#include <Asset/AssetManager/AssetManager.h>

#include "Rendering/Texture/TextureView.h"


namespace dooms::graphics::staticRendererBatchContainerHelper
{
	static const char* const BATCH_RENDERING_SHADER_NAME = "GbufferWriter_BatchedMesh_PBR.glsl";
	static const char* const BATCHABLE_SHADER_NAME = "GbufferWriter_PBR.glsl";
	static dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage BATCHABLE_SHADER_SHADER_TYPE[]
	{
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER,
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER
	};
}

void dooms::graphics::StaticRendererBatchContainer::InitializeBatchRenderingMaterial(Material* const targetMaterial)
{
	dooms::asset::ShaderAsset* const batchRenderingShaderAsset = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>(staticRendererBatchContainerHelper::BATCH_RENDERING_SHADER_NAME);
	D_ASSERT(IsValid(batchRenderingShaderAsset));
	if(IsValid(batchRenderingShaderAsset))
	{
		mBatchRenderingMaterial = dooms::CreateDObject<dooms::graphics::Material>(batchRenderingShaderAsset);
		D_ASSERT(IsValid(mBatchRenderingMaterial));

		const size_t targetTextureCount = targetMaterial->GetTextureViewCount();
		for(size_t textureIndex = 0 ; textureIndex < targetTextureCount ; textureIndex++)
		{
			const TextureView* const textureView = targetMaterial->GetTextureView(textureIndex);
			if(IsValid(textureView))
			{
				mBatchRenderingMaterial->AddTexture(textureView->GetDefaultBindingLocation(), textureView);
			}
		}
	
	}
	D_ASSERT(IsValid(mBatchRenderingMaterial) && mBatchRenderingMaterial->IsHasAnyValidShaderObject());
}

dooms::graphics::StaticRendererBatchContainer::StaticRendererBatchContainer(Material* const targetMaterial)
	: RendererBatchContainer(targetMaterial), mBatchRenderingMaterial(nullptr)
{

	InitializeBatchRenderingMaterial(targetMaterial);

}

void dooms::graphics::StaticRendererBatchContainer::BakeBatchedMesh()
{
	if (IsValid(mBatchedMesh))
	{
		mBatchedMesh->SetIsPendingKill();
	}

	// Bake Batched Mesh with mBatchedMeshRenderers
	mBatchedMesh = dooms::graphics::meshBatchCreater::CreateStaticBatchedMesh(mBatchedRenderers);
	D_ASSERT(IsValid(mBatchedMesh));
}

dooms::graphics::eBatchRenderingType dooms::graphics::StaticRendererBatchContainer::GetBatchRenderingType() const
{
	return eBatchRenderingType::StaticMeshBatch;
}

void dooms::graphics::StaticRendererBatchContainer::BatchedDraw() const
{
	D_ASSERT(IsValid(mBatchRenderingMaterial));

	if(IsValid(mBatchRenderingMaterial) && IsValid(mBatchedMesh))
	{
		mBatchRenderingMaterial->BindMaterial();
		mBatchedMesh->Draw();
	}
}

bool dooms::graphics::StaticRendererBatchContainer::CheckMaterialAcceptable(Material* const material)
{
	bool isAcceptable = true;
	// Material should be GbufferWriter_PBR.glsl

	if(IsValid(material))
	{
		for (dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage batchableShaderType : staticRendererBatchContainerHelper::BATCHABLE_SHADER_SHADER_TYPE)
		{
			dooms::asset::ShaderAsset* const shaderAsset = material->GetShaderAsset(batchableShaderType);
			if(IsValid(shaderAsset))
			{
				if(shaderAsset->GetAssetFileName() != staticRendererBatchContainerHelper::BATCHABLE_SHADER_NAME)
				{
					isAcceptable = false;
					break;
				}
			}
			else
			{
				isAcceptable = false;
				break;
			}
		}
	}

	return isAcceptable;
}

bool dooms::graphics::StaticRendererBatchContainer::CheckRendererAcceptable(Renderer* const renderer) const
{
	return (IsValid(renderer) && renderer->IsChildOf<MeshRenderer>() && CheckMaterialAcceptable(renderer->GetMaterial()));
}
