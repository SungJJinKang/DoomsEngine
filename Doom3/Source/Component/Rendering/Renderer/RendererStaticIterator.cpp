#include "RendererStaticIterator.h"

#include "Renderer.h"
#include "Entity.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

dooms::RendererComponentStaticIterator::RendererComponentStaticIterator()
	: mWorkingRendererListIndex(), mRendererList()
{
	AddToRootObjectList();
}

void dooms::RendererComponentStaticIterator::AddRendererToStaticContainer(Renderer* const renderer)
{
	const size_t currentEntityLayerIndex = renderer->GetOwnerEntityLayerIndex();

	GetSortedRendererInLayer().push_back(renderer);
	GetSortingRendererInLayer().push_back(renderer);
}

void dooms::RendererComponentStaticIterator::RemoveRendererToStaticContainer(const Renderer* const renderer)
{
	std::vector<Renderer*>& workingRendererInLayer = GetSortedRendererInLayer();
	auto workingIter = std::find(workingRendererInLayer.begin(), workingRendererInLayer.end(), renderer);
	if (workingIter != workingRendererInLayer.end())
	{
		swap_popback::vector_swap_popback(workingRendererInLayer, workingIter);
	}

	std::vector<Renderer*>& sortingRenderer = GetSortingRendererInLayer();
	auto referenceIter = std::find(sortingRenderer.begin(), sortingRenderer.end(), renderer);
	if (referenceIter != sortingRenderer.end())
	{
		swap_popback::vector_swap_popback(sortingRenderer, referenceIter);
	}
}


// TODO : Add this to Entity's EntityLayerChanged Callback
void dooms::RendererComponentStaticIterator::OnEntityLayerChanged(Renderer* const renderer)
{
	RemoveRendererToStaticContainer(renderer);
	AddRendererToStaticContainer(renderer);
}

std::vector<dooms::Renderer*>& dooms::RendererComponentStaticIterator::GetSortedRendererInLayer()
{
	return (mWorkingRendererListIndex == 0) ? mRendererList.mRendererList2 : mRendererList.mRendererList1;
}

std::vector<dooms::Renderer*>& dooms::RendererComponentStaticIterator::GetSortingRendererInLayer()
{
	return (mWorkingRendererListIndex == 0) ? mRendererList.mRendererList1 : mRendererList.mRendererList2;
}

void dooms::RendererComponentStaticIterator::ChangeWorkingIndexRenderers()
{
	mWorkingRendererListIndex = (mWorkingRendererListIndex == 0) ? 1 : 0;
}


