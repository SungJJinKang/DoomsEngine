#include "RendererStaticIterator.h"

#include <algorithm>
#include "../Renderer.h"
#include "Entity.h"
#include "../Helper/vector_erase_move_lastelement/vector_swap_erase.h"

using namespace doom;

doom::ComponentStaticIterater<Renderer>::ComponentStaticIterater() : mCurrentEntityLayerIndex{ -1 }, renderer_ptr{ reinterpret_cast<Renderer*>(this) }
{
	this->AddRendererToStaticContainer();
}

doom::ComponentStaticIterater<Renderer>::~ComponentStaticIterater()
{
	this->RemoveRendererToStaticContainer();
}

void doom::ComponentStaticIterater<Renderer>::AddRendererToStaticContainer()
{
	unsigned int currentEntityLayerIndex = renderer_ptr->GetOwnerEntityLayerIndex();

	this_type::mComponentsInLayer[currentEntityLayerIndex].push_back(renderer_ptr);
	this->mCurrentEntityLayerIndex = currentEntityLayerIndex;
}


void doom::ComponentStaticIterater<Renderer>::RemoveRendererToStaticContainer()
{
	unsigned int currentEntityLayerIndex = renderer_ptr->GetOwnerEntityLayerIndex();

	auto iter = std::find(this_type::mComponentsInLayer[currentEntityLayerIndex].begin(), this_type::mComponentsInLayer[currentEntityLayerIndex].end(), renderer_ptr);
	if (iter != this_type::mComponentsInLayer[currentEntityLayerIndex].end())
	{
		std::vector_swap_erase(this_type::mComponentsInLayer[currentEntityLayerIndex], iter);
	}
}


std::pair<typename ComponentStaticIterater<Renderer>::layer_container_type::iterator, typename ComponentStaticIterater<Renderer>::layer_container_type::iterator> doom::ComponentStaticIterater<Renderer>::GetIterWithLayerIndex(unsigned int layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	return std::make_pair(this_type::mComponentsInLayer[layerIndex].begin(), this_type::mComponentsInLayer[layerIndex].end());
}

// TODO : Add this to Entity's EntityLayerChanged Callback
void doom::ComponentStaticIterater<Renderer>::OnEntityLayerChanged(Entity& entity)
{
	this->RemoveRendererToStaticContainer();
	this->AddRendererToStaticContainer();
}