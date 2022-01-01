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
		GetSortedRendererInLayer(cameraIndex).push_back(renderer);
		GetSortingRendererInLayer(cameraIndex).push_back(renderer);
	}

}


void dooms::StaticContainer<Renderer>::RemoveRendererToStaticContainer(const Renderer* const renderer)
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
void dooms::StaticContainer<Renderer>::OnEntityLayerChanged(Renderer* const renderer)
{
	RemoveRendererToStaticContainer(renderer);
	AddRendererToStaticContainer(renderer);
}

std::vector<Renderer*>& dooms::StaticContainer<Renderer>::GetSortedRendererInLayer
(
	const size_t cameraIndex
)
{
	return mRendererList[cameraIndex][mWorkingRendererListIndex];
}

std::vector<Renderer*>& StaticContainer<Renderer>::GetSortingRendererInLayer
(
	const size_t cameraIndex
)
{
	return mRendererList[cameraIndex][(mWorkingRendererListIndex == 0) ? 1 : 0];
}

void StaticContainer<Renderer>::ChangeWorkingIndexRenderers()
{
	mWorkingRendererListIndex = (mWorkingRendererListIndex == 0) ? 1 : 0;
}


