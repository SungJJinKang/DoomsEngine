#include "RendererBatchContainer.h"

#include <Rendering/Renderer/Renderer.h>
#include <vector_erase_move_lastelement/vector_swap_popback.h>


dooms::graphics::RendererBatchContainer::RendererBatchContainer(Material* const targetMaterial)
	: mBatchedMesh(nullptr), mTargetMaterial(targetMaterial)
{
	AddToRootObjectList();
}

bool dooms::graphics::RendererBatchContainer::AddRenderer(Renderer* const Renderer, const bool bakeBatchedMesh)
{
	bool isSuccess = false;

	D_ASSERT(IsValid(Renderer) && Material::Equal(Renderer->GetMaterial(), mTargetMaterial));
	if (IsValid(Renderer) && Material::Equal(Renderer->GetMaterial(), mTargetMaterial))
	{
		if
		(
			fast_find_simd::find_simd_raw
			(
				mBatchedRenderers.data(),
				mBatchedRenderers.data() + mBatchedRenderers.size(),
				Renderer
			) == mBatchedRenderers.data() + mBatchedRenderers.size()
		)
		{
			mBatchedRenderers.push_back(Renderer);

			if (bakeBatchedMesh == true)
			{
				ReBakeBatchedMesh();
			}

			isSuccess = true;
		}
	}

	return isSuccess;
}

void dooms::graphics::RendererBatchContainer::AddRenderer(const std::vector<Renderer*>& Renderers, const bool bakeBatchedMesh)
{
	for(Renderer* Renderer : Renderers)
	{
		AddRenderer(Renderer, false);
	}

	if(bakeBatchedMesh)
	{
		ReBakeBatchedMesh();
	}
}

bool dooms::graphics::RendererBatchContainer::RemoveRenderer(Renderer* const Renderer, const bool bakeBatchedMesh)
{
	bool isSuccess = false;

	if(IsValid(Renderer))
	{
		isSuccess = swap_popback::vector_find_swap_popback(mBatchedRenderers, Renderer);
		if(isSuccess && bakeBatchedMesh)
		{
			ReBakeBatchedMesh();
		}
	}

	return isSuccess;
}
