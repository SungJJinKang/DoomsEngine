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
		rendererBatchContainer = dooms::CreateDObject<StaticRendererBatchContainer>(targetMaterial);
		break;
	default:
		NEVER_HAPPEN;
	}

	D_ASSERT(IsValid(rendererBatchContainer));

	return rendererBatchContainer;
}
