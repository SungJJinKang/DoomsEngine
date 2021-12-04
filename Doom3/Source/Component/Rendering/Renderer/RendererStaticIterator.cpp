#include "RendererStaticIterator.h"

#include "Renderer.h"
#include "Entity.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

using namespace dooms;


StaticContainer<Renderer>::StaticContainer()
{
	AddToRootObjectList();
}

void dooms::StaticContainer<Renderer>::AddRendererToStaticContainer(Renderer* const renderer)
{
	const size_t currentEntityLayerIndex = renderer->GetOwnerEntityLayerIndex();

	for(size_t cameraIndex = 0 ; cameraIndex < MAX_CAMERA_COUNT ; cameraIndex++)
	{
		GetWorkingRendererInLayer(cameraIndex, currentEntityLayerIndex).push_back(renderer);
		GetSortingRendererInLayer(cameraIndex, currentEntityLayerIndex).push_back(renderer);
	}

}


void dooms::StaticContainer<Renderer>::RemoveRendererToStaticContainer(const Renderer* const renderer)
{
	UINT32 currentEntityLayerIndex = renderer->GetOwnerEntityLayerIndex();

	for (size_t cameraIndex = 0; cameraIndex < MAX_CAMERA_COUNT; cameraIndex++)
	{
		std::vector<Renderer*>& workingRendererInLayer = GetWorkingRendererInLayer(cameraIndex, currentEntityLayerIndex);
		auto workingIter = std::find(workingRendererInLayer.begin(), workingRendererInLayer.end(), renderer);
		if (workingIter != workingRendererInLayer.end())
		{
			swap_popback::vector_swap_popback(workingRendererInLayer, workingIter);
		}

		std::vector<Renderer*>& sortingRendererInLayer = GetSortingRendererInLayer(cameraIndex, currentEntityLayerIndex);
		auto referenceIter = std::find(sortingRendererInLayer.begin(), sortingRendererInLayer.end(), renderer);
		if (referenceIter != sortingRendererInLayer.end())
		{
			swap_popback::vector_swap_popback(sortingRendererInLayer, referenceIter);
		}
	}
}


// TODO : Add this to Entity's EntityLayerChanged Callback
void dooms::StaticContainer<Renderer>::OnEntityLayerChanged(Renderer* const renderer)
{
	RemoveRendererToStaticContainer(renderer);
	AddRendererToStaticContainer(renderer);
}

std::vector<Renderer*>& dooms::StaticContainer<Renderer>::GetWorkingRendererInLayer(const size_t cameraIndex, const size_t layerIndex)
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


