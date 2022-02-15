#include "StaticRendererBatchContainer.h"

#include <Rendering/Renderer/MeshRenderer.h>
#include "meshBatchCreater.h"

void dooms::graphics::StaticRendererBatchContainer::GenerateBatchRenderingMaterialFromTargetMaterial()
{
}

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

void dooms::graphics::StaticRendererBatchContainer::BatchedDraw() const
{
	D_ASSERT(IsValid(BatchRenderingMaterial));

	if(IsValid(BatchRenderingMaterial))
	{
		BatchRenderingMaterial->BindMaterial();
	}
}

bool dooms::graphics::StaticRendererBatchContainer::CheckMaterialAcceptable(Material* const material)
{
	// Material should be GbufferWriter_PBR.glsl
	D_ASSERT(false);
	return false;
}

bool dooms::graphics::StaticRendererBatchContainer::CheckRendererAcceptable(Renderer* const renderer) const
{
	return (IsValid(renderer) && renderer->IsChildOf<MeshRenderer>());
}
