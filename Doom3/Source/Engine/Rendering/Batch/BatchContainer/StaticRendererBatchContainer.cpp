#include "StaticRendererBatchContainer.h"

#include <Rendering/Renderer/MeshRenderer.h>
#include "meshBatchCreater.h"

dooms::graphics::StaticRendererBatchContainer::StaticRendererBatchContainer(Material* const targetMaterial)
	: RendererBatchContainer(targetMaterial)
{
}

void dooms::graphics::StaticRendererBatchContainer::ReBakeBatchedMesh()
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
