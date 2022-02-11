#include "RendererStaticIterator.h"

#include "Renderer.h"
#include "Entity.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

dooms::StaticContainer<dooms::Renderer>::StaticContainer()
{
	AddToRootObjectList();
}

void dooms::StaticContainer<dooms::Renderer>::AddRendererToStaticContainer(Renderer* const renderer)
{
	const size_t currentEntityLayerIndex = renderer->GetOwnerEntityLayerIndex();

	for(size_t cameraIndex = 0 ; cameraIndex < MAX_CAMERA_COUNT ; cameraIndex++)
	{
		GetSortedRendererInLayer(cameraIndex).push_back(renderer);
		GetSortingRendererInLayer(cameraIndex).push_back(renderer);
	}

}

void dooms::StaticContainer<dooms::Renderer>::RemoveRendererToStaticContainer(const Renderer* const renderer)
{
	for (size_t cameraIndex = 0; cameraIndex < MAX_CAMERA_COUNT; cameraIndex++)
	{
		std::vector<Renderer*>& workingRendererInLayer = GetSortedRendererInLayer(cameraIndex);
		auto workingIter = std::find(workingRendererInLayer.begin(), workingRendererInLayer.end(), renderer);
		if (workingIter != workingRendererInLayer.end())
		{
			swap_popback::vector_swap_popback(workingRendererInLayer, workingIter);
		}

		std::vector<Renderer*>& sortingRenderer = GetSortingRendererInLayer(cameraIndex);
		auto referenceIter = std::find(sortingRenderer.begin(), sortingRenderer.end(), renderer);
		if (referenceIter != sortingRenderer.end())
		{
			swap_popback::vector_swap_popback(sortingRenderer, referenceIter);
		}
	}
}


// TODO : Add this to Entity's EntityLayerChanged Callback
void dooms::StaticContainer<dooms::Renderer>::OnEntityLayerChanged(Renderer* const renderer)
{
	RemoveRendererToStaticContainer(renderer);
	AddRendererToStaticContainer(renderer);
}

std::vector<dooms::Renderer*>& dooms::StaticContainer<dooms::Renderer>::GetSortedRendererInLayer
(
	const size_t cameraIndex
)
{
	return mRendererList[cameraIndex][mWorkingRendererListIndex];
}

std::vector<dooms::Renderer*>& dooms::StaticContainer<dooms::Renderer>::GetSortingRendererInLayer
(
	const size_t cameraIndex
)
{
	return mRendererList[cameraIndex][(mWorkingRendererListIndex == 0) ? 1 : 0];
}

void dooms::StaticContainer<dooms::Renderer>::ChangeWorkingIndexRenderers()
{
	mWorkingRendererListIndex = (mWorkingRendererListIndex == 0) ? 1 : 0;
}


