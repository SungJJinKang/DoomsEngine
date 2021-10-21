#include "RendererStaticIterator.h"

#include "Renderer.h"
#include "Entity.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

using namespace doom;

doom::StaticContainer<Renderer>::StaticContainer() : mRenderer_ptr{ nullptr }
{
	//AddRendererToStaticContainer(); at contructor, entity is not set
}

doom::StaticContainer<Renderer>::~StaticContainer()
{
	RemoveRendererToStaticContainer();
}

StaticContainer<Renderer>::StaticContainer(const StaticContainer&) : mRenderer_ptr{ nullptr }
{
}

StaticContainer<Renderer>& StaticContainer<Renderer>::operator=(const StaticContainer&)
{
	mRenderer_ptr = nullptr;
	return *this;
}

StaticContainer<Renderer>::StaticContainer(StaticContainer&&) noexcept : mRenderer_ptr{ nullptr }
{
}

StaticContainer<Renderer>& StaticContainer<Renderer>::operator=(StaticContainer&&) noexcept
{
	mRenderer_ptr = nullptr;
	return *this;
}


void doom::StaticContainer<Renderer>::AddRendererToStaticContainer()
{
	mRenderer_ptr = static_cast<Renderer*>(this);

	const size_t currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	for(size_t cameraIndex = 0 ; cameraIndex < MAX_CAMERA_COUNT ; cameraIndex++)
	{
		GetWorkingRendererInLayer(cameraIndex, currentEntityLayerIndex).push_back(mRenderer_ptr);
		GetSortingRendererInLayer(cameraIndex, currentEntityLayerIndex).push_back(mRenderer_ptr);
	}

}


void doom::StaticContainer<Renderer>::RemoveRendererToStaticContainer()
{
	UINT32 currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	for (size_t cameraIndex = 0; cameraIndex < MAX_CAMERA_COUNT; cameraIndex++)
	{
		std::vector<Renderer*>& workingRendererInLayer = GetWorkingRendererInLayer(cameraIndex, currentEntityLayerIndex);
		auto workingIter = std::find(workingRendererInLayer.begin(), workingRendererInLayer.end(), mRenderer_ptr);
		if (workingIter != workingRendererInLayer.end())
		{
			std::vector_swap_popback(workingRendererInLayer, workingIter);
		}

		std::vector<Renderer*>& sortingRendererInLayer = GetSortingRendererInLayer(cameraIndex, currentEntityLayerIndex);
		auto referenceIter = std::find(sortingRendererInLayer.begin(), sortingRendererInLayer.end(), mRenderer_ptr);
		if (referenceIter != sortingRendererInLayer.end())
		{
			std::vector_swap_popback(sortingRendererInLayer, referenceIter);
		}
	}
}


// TODO : Add this to Entity's EntityLayerChanged Callback
void doom::StaticContainer<Renderer>::OnEntityLayerChanged(Entity& entity)
{
	RemoveRendererToStaticContainer();
	AddRendererToStaticContainer();
}

std::vector<Renderer*>& doom::StaticContainer<Renderer>::GetWorkingRendererInLayer(const size_t cameraIndex, const size_t layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return this_type::mRenderersInLayer[cameraIndex][mWorkingRendererListIndex][layerIndex];
}

std::vector<Renderer*>& StaticContainer<Renderer>::GetSortingRendererInLayer(const size_t cameraIndex, const size_t layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return this_type::mRenderersInLayer[cameraIndex][(mWorkingRendererListIndex == 0) ? 1 : 0][layerIndex];
}

void StaticContainer<Renderer>::ChangeWorkingIndexRenderers()
{
	mWorkingRendererListIndex = (mWorkingRendererListIndex == 0) ? 1 : 0;
}


