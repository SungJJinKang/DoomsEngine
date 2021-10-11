#include "RendererStaticIterator.h"

#include "Renderer.h"
#include "Rendering/Camera.h"
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


void doom::StaticContainer<Renderer>::AddRendererToStaticContainer()
{
	if (mRenderer_ptr == nullptr)
	{
		mRenderer_ptr = dynamic_cast<Renderer*>(this);
	}
	D_ASSERT(mRenderer_ptr != nullptr);

	const size_t currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	for(size_t cameraIndex = 0 ; cameraIndex < MAX_CAMERA_COUNT ; cameraIndex++)
	{
		GetWorkingRendererInLayer(cameraIndex, currentEntityLayerIndex).push_back(mRenderer_ptr);
		GetReferenceRendererInLayer(cameraIndex, currentEntityLayerIndex).push_back(mRenderer_ptr);
	}

}


void doom::StaticContainer<Renderer>::RemoveRendererToStaticContainer()
{
	unsigned int currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	for (size_t cameraIndex = 0; cameraIndex < MAX_CAMERA_COUNT; cameraIndex++)
	{
		std::vector<Renderer*>& workingRendererInLayer = GetWorkingRendererInLayer(cameraIndex, currentEntityLayerIndex);
		auto workingIter = std::find(workingRendererInLayer.begin(), workingRendererInLayer.end(), mRenderer_ptr);
		if (workingIter != workingRendererInLayer.end())
		{
			std::vector_swap_popback(workingRendererInLayer, workingIter);
		}

		std::vector<Renderer*>& referenceRendererInLayer = GetReferenceRendererInLayer(cameraIndex, currentEntityLayerIndex);
		auto referenceIter = std::find(referenceRendererInLayer.begin(), referenceRendererInLayer.end(), mRenderer_ptr);
		if (referenceIter != referenceRendererInLayer.end())
		{
			std::vector_swap_popback(referenceRendererInLayer, referenceIter);
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
	return this_type::mRenderersInLayer[cameraIndex][mWorkingIndexRenderersInLayerVariable][layerIndex];
}

std::vector<Renderer*>& StaticContainer<Renderer>::GetReferenceRendererInLayer(const size_t cameraIndex, const size_t layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return this_type::mRenderersInLayer[cameraIndex][(mWorkingIndexRenderersInLayerVariable == 0) ? 1 : 0][layerIndex];
}

void StaticContainer<Renderer>::ChangeWorkingIndexRenderers()
{
	mWorkingIndexRenderersInLayerVariable = (mWorkingIndexRenderersInLayerVariable == 0) ? 1 : 0;
}


