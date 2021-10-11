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

std::vector<Renderer*>& doom::StaticContainer<Renderer>::GetRendererInLayer(const size_t layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return this_type::mRenderersInLayer[layerIndex];
}


