#include "batchContainerFactory.h"

#include "StaticRendererBatchContainer.h"

dooms::graphics::RendererBatchContainer* dooms::graphics::batchContainerFactory::CreateRendererBatchContainer
(
	Material* const targetMaterial,
	const eBatchRenderingType batchRenderingType
)
{
	dooms::graphics::RendererBatchContainer* rendererBatchContainer = nullptr;

	switch (batchRenderingType)
	{
	case StaticMeshBatch:
		if(StaticRendererBatchContainer::CheckMaterialAcceptable(targetMaterial) == true)
		{
			rendererBatchContainer = dooms::CreateDObject<StaticRendererBatchContainer>(targetMaterial);
		}
		else
		{
			D_ASSERT_LOG(false, "This material can't be used for StaticRendererBatchContainer");
		}
		break;
	default:
		ASSUME_ZERO;
	}

	D_ASSERT(IsValid(rendererBatchContainer));

	return rendererBatchContainer;
}
