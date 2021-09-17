#include "RendererStaticIterator.h"

#include <algorithm>
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




void doom::StaticContainer<Renderer>::CacheDistanceFromRenderersToCamera(std::vector<Renderer*>& renderersInLayer, const std::vector<Camera*>& cameras)
{
	for (size_t cameraIndex = 0; cameraIndex < cameras.size(); cameraIndex++)
	{
		for (Renderer* renderer : renderersInLayer)
		{
			renderer->CacheDistanceToCamera(cameraIndex, cameras[cameraIndex]);
		}
	}
}

void doom::StaticContainer<Renderer>::CacheDistanceFromRenderersToCamera(const std::vector<Camera*> cameras)
{
	for (std::vector<Renderer*>& renderersInLayer : this_type::mRenderersInLayer)
	{
		CacheDistanceFromRenderersToCamera(renderersInLayer, cameras);
	}
}

void doom::StaticContainer<Renderer>::AddRendererToStaticContainer()
{
	if (mRenderer_ptr == nullptr)
	{
		mRenderer_ptr = dynamic_cast<Renderer*>(this);
	}
	D_ASSERT(mRenderer_ptr != nullptr);

	unsigned int currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	this_type::mRenderersInLayer[currentEntityLayerIndex].push_back(mRenderer_ptr);
}


void doom::StaticContainer<Renderer>::RemoveRendererToStaticContainer()
{
	unsigned int currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	auto iter = std::find(this_type::mRenderersInLayer[currentEntityLayerIndex].begin(), this_type::mRenderersInLayer[currentEntityLayerIndex].end(), mRenderer_ptr);
	if (iter != this_type::mRenderersInLayer[currentEntityLayerIndex].end())
	{
		std::vector_swap_popback(this_type::mRenderersInLayer[currentEntityLayerIndex], iter);
	}
}


// TODO : Add this to Entity's EntityLayerChanged Callback
void doom::StaticContainer<Renderer>::OnEntityLayerChanged(Entity& entity)
{
	RemoveRendererToStaticContainer();
	AddRendererToStaticContainer();
}

const std::vector<Renderer*>& doom::StaticContainer<Renderer>::GetRendererInLayer(const unsigned int layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return this_type::mRenderersInLayer[layerIndex];
}

void doom::StaticContainer<Renderer>::SortByDistanceToCamera(const size_t layerIndex, const size_t cameraIndex)
{
	std::sort(
		this_type::mRenderersInLayer[layerIndex].begin(), this_type::mRenderersInLayer[layerIndex].end(),
		[cameraIndex](const Renderer* const lhs, const Renderer* const rhs)
		{
			return lhs->GetDistanceToCamera(cameraIndex) < rhs->GetDistanceToCamera(cameraIndex);
		}
	);
}



void doom::StaticContainer<Renderer>::SortByDistanceToCamera(const Camera* const camera, const size_t cameraIndex)
{
	for (size_t layerIndex = 0; layerIndex < this_type::mRenderersInLayer.size() ; layerIndex++)
	{
		SortByDistanceToCamera(layerIndex, cameraIndex);
	}
	

}

