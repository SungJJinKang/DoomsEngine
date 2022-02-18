#include "BatchRenderingManager.h"

#include <Rendering/Renderer/Renderer.h>
#include "BatchContainer/RendererBatchContainer.h"
#include "BatchContainer/batchContainerFactory.h"


dooms::graphics::RendererBatchContainer* dooms::graphics::BatchRenderingManager::CreateBatchedRendererContainer
(
	Material* const material, const eBatchRenderingType batchRenderingType
)
{
	D_ASSERT(IsValid(material) && IsValid(material) && material->IsHasAnyValidShaderObject());

	dooms::graphics::RendererBatchContainer* batchedRendererContainer = nullptr;

	D_ASSERT(IsValid(material) && material->IsHasAnyValidShaderObject());
	if (IsValid(material) && material->IsHasAnyValidShaderObject())
	{
		auto node = mBatchedRendererContainers.find(material->GetMaterialHashValue());
		if (node == mBatchedRendererContainers.end())
		{
			const auto pair = std::make_pair(material->GetMaterialHashValue(), std::vector<dooms::graphics::RendererBatchContainer*>{});
			mBatchedRendererContainers.emplace(pair);
		}

		batchedRendererContainer = dooms::graphics::batchContainerFactory::CreateRendererBatchContainer(material, batchRenderingType);
		node->second.push_back(batchedRendererContainer);
	}

	D_ASSERT(IsValid(batchedRendererContainer) && batchedRendererContainer->GetBatchRenderingType() == batchRenderingType);

	return batchedRendererContainer;
}

dooms::graphics::RendererBatchContainer* dooms::graphics::BatchRenderingManager::FindBatchedRendererContainer
(
	Renderer* const renderer
) const
{
	dooms::graphics::RendererBatchContainer* batchedRendererContainer = nullptr;

	if (IsValid(renderer) && IsValid(renderer->GetMaterial()) && renderer->GetMaterial()->IsHasAnyValidShaderObject())
	{
		auto node = mBatchedRendererContainers.find(renderer->GetMaterial()->GetMaterialHashValue());
		if (node != mBatchedRendererContainers.end())
		{
			for(dooms::graphics::RendererBatchContainer* batchContainer : node->second)
			{
				D_ASSERT(IsValid(batchContainer));
				if(batchContainer->HasRenderer(renderer) == true)
				{
					batchedRendererContainer = batchContainer;
					break;
				}
			}
		}
	}

	return batchedRendererContainer;
}

dooms::graphics::BatchRenderingManager::BatchRenderingManager() : bPauseBakeBatchMesh(true)
{
}

bool dooms::graphics::BatchRenderingManager::AddRendererToBatchRendering(Renderer* const renderer, const eBatchRenderingType batchRenderingType)
{
	bool isSuccess = false;
	
	if(IsValid(renderer) && IsValid(renderer->GetMaterial()))
	{
		bool isCreateNewContainer = true;
		const UINT64 materialHashValue = renderer->GetMaterial()->GetMaterialHashValue();
		auto batchedRendererContainerNode = mBatchedRendererContainers.find(materialHashValue);

		if(batchedRendererContainerNode == mBatchedRendererContainers.end())
		{
			const auto pair = std::make_pair(materialHashValue, std::vector<dooms::graphics::RendererBatchContainer*>{});
			batchedRendererContainerNode = mBatchedRendererContainers.emplace(pair).first;
		}

		if(batchedRendererContainerNode->second.empty() == false)
		{
			const eRendererBatchContainerState state = batchedRendererContainerNode->second.back()->CheckRendererAcceptable(renderer);
			switch (state)
			{
			case Acceptable:
				isSuccess = batchedRendererContainerNode->second.back()->AddRenderer(renderer, !bPauseBakeBatchMesh);
				D_ASSERT(isSuccess == true);
				isCreateNewContainer = false;
				break;
			case Unacceptable:
				isSuccess = false;
				isCreateNewContainer = false;
				break;
			case AcceptableButContainerIsFull: 
				isCreateNewContainer = true;
				break;
			default:
				NEVER_HAPPEN;
			}
		}

		if(isCreateNewContainer == true)
		{
			dooms::graphics::RendererBatchContainer* const rendererBatchContainer = dooms::graphics::batchContainerFactory::CreateRendererBatchContainer(renderer->GetMaterial(), batchRenderingType);
			D_ASSERT(IsValid(rendererBatchContainer));
			if(IsValid(rendererBatchContainer))
			{
				batchedRendererContainerNode->second.push_back(rendererBatchContainer);
				isSuccess = rendererBatchContainer->AddRenderer(renderer, !bPauseBakeBatchMesh);
			}
		}
		
	}

	return isSuccess;
}

bool dooms::graphics::BatchRenderingManager::RemoveRendererFromBatchRendering(Renderer* const renderer)
{
	bool isSuccess = false;
	
	if (IsValid(renderer) && IsValid(renderer->GetMaterial()))
	{
		dooms::graphics::RendererBatchContainer* batchedRendererContainer = FindBatchedRendererContainer(renderer);
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
		std::vector<RendererBatchContainer*>& rendererBatchContainers = rendererBatchContainerNode.second;
		for (RendererBatchContainer* rendererBatchContainer : rendererBatchContainers)
		{
			D_ASSERT(IsValid(rendererBatchContainer));
			if (IsValid(rendererBatchContainer))
			{
				rendererBatchContainer->BatchedDraw();
			}
		}
	}
}

void dooms::graphics::BatchRenderingManager::SetPauseBakeBatchMesh(const bool pauseBakeBatchMesh)
{
	if(pauseBakeBatchMesh == false && bPauseBakeBatchMesh == true)
	{
		BakeAllRendererBatchContainer();
	}
	bPauseBakeBatchMesh = pauseBakeBatchMesh;
}

void dooms::graphics::BatchRenderingManager::BakeAllRendererBatchContainer()
{
	for(auto& rendererBatchContainerNode : mBatchedRendererContainers)
	{
		std::vector<RendererBatchContainer*>& rendererBatchContainers = rendererBatchContainerNode.second;
		for(RendererBatchContainer* rendererBatchContainer : rendererBatchContainers)
		{
			D_ASSERT(IsValid(rendererBatchContainer));
			if (IsValid(rendererBatchContainer))
			{
				rendererBatchContainer->BakeBatchedMesh();
			}
		}
	}
}
