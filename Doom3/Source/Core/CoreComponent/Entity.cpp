#include "Entity.h"
#include "../../Component/Transform.h"

doom::Entity::Entity() : mEntityName{}, mTransform{}, mComponents{}
{
	this->mTransform = &(this->AddComponent<doom::Transform>());
}

void doom::Entity::UpdateComponents()
{
	for (auto& component : this->mComponents)
	{
		component->OnUpdateComponent_Internal();
		component->OnUpdateComponent();
	}
}
