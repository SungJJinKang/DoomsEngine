#include "Entity.h"

#include <algorithm>

#include"Scene.h"


using namespace doom;

Entity::Entity(Entity* parent) : mEntityName{}, mPlainComponents{}, mParent{ parent }, mChilds{}
{
	this->mTransform = this->AddComponent<Transform>();
}

Entity::~Entity()
{
	this->ClearComponents();
}


void doom::Entity::InitEntity()
{
}

void doom::Entity::UpdateEntity()
{
}

void doom::Entity::OnEndOfFramePlainComponentsAndEntity()
{
	this->EndOfFrame_PlainComponent();
	this->FrameDirtyChecker_EndOfFrame();
}

void doom::Entity::Update_PlainComponent()
{
	for (auto& plainComponent : this->mPlainComponents)
	{
		plainComponent->UpdateComponent_Internal();
		plainComponent->UpdateComponent();
	}
}

void doom::Entity::EndOfFrame_PlainComponent()
{
	for (auto& plainComponent : this->mPlainComponents)
	{
		plainComponent->OnEndOfFrame_Component_Internal();
		plainComponent->OnEndOfFrame_Component();
	}
}

void Entity::OnActivated()
{
	this->SetDirtyTrueAtThisFrame();
}

std::string_view Entity::GetEntityName() const
{
	return this->mEntityName;
}


void Entity::AddLayerChangedCallback(void(*callback_ptr)(Entity&))
{
#ifdef DEBUG_MODE
	//check is callback is already contained
	auto iter = std::find(this->mLayerIndexChangedCallback.begin(), this->mLayerIndexChangedCallback.end(), callback_ptr);
	D_ASSERT(iter == this->mLayerIndexChangedCallback.end());
#endif

	this->mLayerIndexChangedCallback.push_back(callback_ptr);
}

void Entity::RemoveLayerChangedCallback(void(*callback_ptr)(Entity&))
{
	auto iter = std::find(this->mLayerIndexChangedCallback.begin(), this->mLayerIndexChangedCallback.end(), callback_ptr);
	D_ASSERT(iter != this->mLayerIndexChangedCallback.end());

	this->mLayerIndexChangedCallback.erase(iter);
}

void Entity::SetLayerIndex(unsigned int layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	this->mLayerIndex = layerIndex;

	for (auto& callback : this->mLayerIndexChangedCallback)
	{
		callback(*this);
	}
}

void Entity::Destroy()
{
	//Work Flow : Scene::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	Scene::GetCurrentWorld()->DestroyEntity(*this);
	
}

