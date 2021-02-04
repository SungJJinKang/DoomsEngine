#include "Entity.h"

#include "../../Component/Transform.h"
#include"World.h"

doom::Entity::Entity(Entity* parent) : mEntityName{}, mTransform{}, mComponents{}, mParent{ parent }, mChilds{}
{
	this->mTransform = &(this->AddComponent_Internal<doom::Transform>());
}

doom::Entity::~Entity()
{
	this->ClearComponents();
}

void doom::Entity::Destroy()
{
	World::DestroyEntity(*this);
}

void doom::Entity::UpdateComponents()
{
	for (auto& component : this->mComponents)
	{
		component->OnUpdateComponent_Internal();
		component->OnUpdateComponent();
	}
}
