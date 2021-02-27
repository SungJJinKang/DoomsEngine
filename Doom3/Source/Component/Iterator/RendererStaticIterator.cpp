#include "RendererStaticIterator.h"

#include <algorithm>
#include "../Renderer.h"
#include "Entity.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_erase.h"

using namespace doom;

doom::StaticContainer<Renderer>::StaticContainer() : mRenderer_ptr{ nullptr }
{
	//this->AddRendererToStaticContainer(); at contructor, entity is not set
}

doom::StaticContainer<Renderer>::~StaticContainer()
{
	this->RemoveRendererToStaticContainer();
}

void doom::StaticContainer<Renderer>::AddRendererToStaticContainer()
{
	if (mRenderer_ptr == nullptr)
	{
		mRenderer_ptr = dynamic_cast<Renderer*>(this);
	}
	D_ASSERT(mRenderer_ptr != nullptr);

	unsigned int currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	this_type::mComponentsInLayer[currentEntityLayerIndex].push_back(mRenderer_ptr);
}


void doom::StaticContainer<Renderer>::RemoveRendererToStaticContainer()
{
	unsigned int currentEntityLayerIndex = mRenderer_ptr->GetOwnerEntityLayerIndex();

	auto iter = std::find(this_type::mComponentsInLayer[currentEntityLayerIndex].begin(), this_type::mComponentsInLayer[currentEntityLayerIndex].end(), mRenderer_ptr);
	if (iter != this_type::mComponentsInLayer[currentEntityLayerIndex].end())
	{
		std::vector_swap_erase(this_type::mComponentsInLayer[currentEntityLayerIndex], iter);
	}
}


std::pair<Renderer**, size_t> doom::StaticContainer<Renderer>::GetAllComponentsWithLayerIndex(unsigned int layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return std::make_pair(this_type::mComponentsInLayer[layerIndex].data(), this_type::mComponentsInLayer[layerIndex].size());
}

// TODO : Add this to Entity's EntityLayerChanged Callback
void doom::StaticContainer<Renderer>::OnEntityLayerChanged(Entity& entity)
{
	this->RemoveRendererToStaticContainer();
	this->AddRendererToStaticContainer();
}