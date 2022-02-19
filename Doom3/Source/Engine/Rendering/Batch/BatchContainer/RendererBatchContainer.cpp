#include "RendererBatchContainer.h"

#include <Rendering/Renderer/Renderer.h>
#include <vector_erase_move_lastelement/vector_swap_popback.h>


dooms::graphics::RendererBatchContainer::RendererBatchContainer(Material* const targetMaterial)
	: mBatchedMesh(nullptr), mTargetMaterial(targetMaterial), bmIsRendererListDirty(true)
{
	AddToRootObjectList();
}

bool dooms::graphics::RendererBatchContainer::AddRenderer(Renderer* const renderer, const bool bakeBatchedMesh)
{
	bool isSuccess = false;

	D_ASSERT(IsValid(renderer) && Material::Equal(renderer->GetMaterial(), mTargetMaterial));
	if (IsValid(renderer) && CheckRendererAcceptable(renderer) == eRendererBatchContainerState::Acceptable && Material::Equal(renderer->GetMaterial(), mTargetMaterial))
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
			bmIsRendererListDirty = true;

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
		bmIsRendererListDirty = true;

		if(isSuccess && bakeBatchedMesh)
		{
			BakeBatchedMesh();
		}
	}

	return isSuccess;
}

bool dooms::graphics::RendererBatchContainer::HasRenderer(Renderer* const renderer) const
{
	bool isHasRenderer = false;

	if (IsValid(renderer))
	{
		isHasRenderer = (fast_find_simd::find_simd(mBatchedRenderers.begin(), mBatchedRenderers.end(), renderer) != mBatchedRenderers.end());
	}

	return isHasRenderer;
}

std::vector<dooms::Renderer*>& dooms::graphics::RendererBatchContainer::GetBatchedRenderers()
{
	return mBatchedRenderers;
}

size_t dooms::graphics::RendererBatchContainer::GetBatchedRendererCount() const
{
	return mBatchedRenderers.size();
}

const std::vector<dooms::Renderer*>& dooms::graphics::RendererBatchContainer::GetBatchedRenderers() const
{
	return mBatchedRenderers;
}
