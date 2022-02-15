#include "BatchRenderingManager.h"

#include <Rendering/Renderer/Renderer.h>
#include "BatchContainer/RendererBatchContainer.h"
#include "BatchContainer/batchContainerFactory.h"

dooms::graphics::RendererBatchContainer* dooms::graphics::BatchRenderingManager::CreateOrFindBatchedRendererContainer
(
	Material* const material, const eBatchRenderingType batchRenderingType
)
{
	D_ASSERT(IsValid(Renderer) && IsValid(Renderer->GetMaterial()) && Renderer->GetMaterial()->IsHasAnyValidShaderObject());

	dooms::graphics::RendererBatchContainer* batchedRendererContainer = nullptr;

	if(IsValid(material) && material->IsHasAnyValidShaderObject())
	{
		auto node = mBatchedRendererContainers.find(material->GetMaterialHashValue());
		if (node == mBatchedRendererContainers.end())
		{
			batchedRendererContainer = dooms::graphics::batchContainerFactory::CreateRendererBatchContainer(material, batchRenderingType);
			mBatchedRendererContainers.emplace(material->GetMaterialHashValue(), batchedRendererContainer);
		}
		else
		{
			batchedRendererContainer = node->second;
		}
	}
	
	D_ASSERT(IsValid(batchedRendererContainer) && batchedRendererContainer->GetBatchRenderingType() == batchRenderingType);

	return batchedRendererContainer;
}

dooms::graphics::RendererBatchContainer* dooms::graphics::BatchRenderingManager::FindBatchedRendererContainer
(
	Material* const material
) const
{
	dooms::graphics::RendererBatchContainer* batchedRendererContainer = nullptr;

	if (IsValid(material) && material->IsHasAnyValidShaderObject())
	{
		auto node = mBatchedRendererContainers.find(material->GetMaterialHashValue());
		if (node != mBatchedRendererContainers.end())
		{
			batchedRendererContainer = node->second;
		}
	}

	return batchedRendererContainer;
}

dooms::graphics::BatchRenderingManager::BatchRenderingManager()
{
}

bool dooms::graphics::BatchRenderingManager::AddRendererToBatchRendering(Renderer* const renderer, const eBatchRenderingType batchRenderingType)
{
	bool isSuccess = false;

	D_ASSERT(IsValid(Renderer) && IsValid(Renderer->GetMaterial()));
	if(IsValid(renderer) && IsValid(renderer->GetMaterial()))
	{
		dooms::graphics::RendererBatchContainer* batchedRendererContainer = CreateOrFindBatchedRendererContainer(renderer->GetMaterial(), batchRenderingType);
		D_ASSERT(IsValid(batchedRendererContainer));

		if(IsValid(batchedRendererContainer) && batchedRendererContainer->GetBatchRenderingType() == batchRenderingType)
		{
			isSuccess = batchedRendererContainer->AddRenderer(renderer);
		}
	}

	return isSuccess;
}

bool dooms::graphics::BatchRenderingManager::RemoveRendererFromBatchRendering(Renderer* const renderer)
{
	bool isSuccess = false;

	D_ASSERT(IsValid(Renderer) && IsValid(Renderer->GetMaterial()));
	if (IsValid(renderer) && IsValid(renderer->GetMaterial()))
	{
		dooms::graphics::RendererBatchContainer* batchedRendererContainer = FindBatchedRendererContainer(renderer->GetMaterial());
		D_ASSERT(IsValid(batchedRendererContainer));
		if (IsValid(batchedRendererContainer))
		{
			isSuccess = batchedRendererContainer->RemoveRenderer(renderer);
		}
	}

	return isSuccess;
}
