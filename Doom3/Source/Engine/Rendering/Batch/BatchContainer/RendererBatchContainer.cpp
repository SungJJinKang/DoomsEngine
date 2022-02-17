#include "RendererBatchContainer.h"

#include <Rendering/Renderer/Renderer.h>
#include <vector_erase_move_lastelement/vector_swap_popback.h>


dooms::graphics::RendererBatchContainer::RendererBatchContainer(Material* const targetMaterial)
	: mBatchedMesh(nullptr), mTargetMaterial(targetMaterial)
{
	AddToRootObjectList();
}

bool dooms::graphics::RendererBatchContainer::AddRenderer(Renderer* const renderer, const bool bakeBatchedMesh)
{
	bool isSuccess = false;

	D_ASSERT(IsValid(renderer) && Material::Equal(renderer->GetMaterial(), mTargetMaterial));
	if (IsValid(renderer) && CheckRendererAcceptable(renderer) && Material::Equal(renderer->GetMaterial(), mTargetMaterial))
	{
		if
		(
			fast_find_simd::find_simd_raw
			(
				mBatchedRenderers.data(),
				mBatchedRenderers.data() + mBatchedRenderers.size(),
				renderer
			) == mBatchedRenderers.data() + mBatchedRenderers.size()
		)
		{
			mBatchedRenderers.push_back(renderer);

			if (bakeBatchedMesh == true)
			{
				BakeBatchedMesh();
			}

			isSuccess = true;
		}
	}

	return isSuccess;
}

void dooms::graphics::RendererBatchContainer::AddRenderer(const std::vector<Renderer*>& renderers, const bool bakeBatchedMesh)
{
	for(Renderer* Renderer : renderers)
	{
		AddRenderer(Renderer, false);
	}

	if(bakeBatchedMesh)
	{
		BakeBatchedMesh();
	}
}

bool dooms::graphics::RendererBatchContainer::RemoveRenderer(Renderer* const renderer, const bool bakeBatchedMesh)
{
	bool isSuccess = false;

	if(IsValid(renderer))
	{
		isSuccess = swap_popback::vector_find_swap_popback(mBatchedRenderers, renderer);
		if(isSuccess && bakeBatchedMesh)
		{
			BakeBatchedMesh();
		}
	}

	return isSuccess;
}
