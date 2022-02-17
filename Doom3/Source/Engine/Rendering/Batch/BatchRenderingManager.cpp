#include "BatchRenderingManager.h"

#include <Rendering/Renderer/Renderer.h>
#include "BatchContainer/RendererBatchContainer.h"
#include "BatchContainer/batchContainerFactory.h"

dooms::graphics::RendererBatchContainer* dooms::graphics::BatchRenderingManager::CreateOrFindBatchedRendererContainer
(
	Material* const material, const eBatchRenderingType batchRenderingType
)
{
	D_ASSERT(IsValid(material) && IsValid(material) && material->IsHasAnyValidShaderObject());

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
	
	if(IsValid(renderer) && IsValid(renderer->GetMaterial()))
	{
		dooms::graphics::RendererBatchContainer* batchedRendererContainer = CreateOrFindBatchedRendererContainer(renderer->GetMaterial(), batchRenderingType);
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
	
	if (IsValid(renderer) && IsValid(renderer->GetMaterial()))
	{
		dooms::graphics::RendererBatchContainer* batchedRendererContainer = FindBatchedRendererContainer(renderer->GetMaterial());
		if (IsValid(batchedRendererContainer))
		{
			isSuccess = batchedRendererContainer->RemoveRenderer(renderer);
		}
	}

	return isSuccess;
}

void dooms::graphics::BatchRenderingManager::DrawAllBatchedRendererContainers() const
{
	for(auto rendererBatchContainerNode : mBatchedRendererContainers)
	{
		RendererBatchContainer* rendererBatchContainer = rendererBatchContainerNode.second;
		if(IsValid(rendererBatchContainer))
		{
			rendererBatchContainer->BatchedDraw();
		}
	}
}
