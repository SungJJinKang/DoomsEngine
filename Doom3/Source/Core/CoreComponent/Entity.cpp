#include "Entity.h"

#include "../../Component/Transform.h"
#include"World.h"

doom::Entity::Entity(Entity* parent) : mEntityName{}, mPlainComponents{}, mParent{ parent }, mChilds{}
{
	this->mTransform = this->AddComponent<doom::Transform>();
}

doom::Entity::~Entity()
{
	this->ClearComponents();
}

void doom::Entity::Destroy()
{
	//Work Flow : World::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	World::GetCurrentWorld().DestroyEntity(*this);
	
}

void doom::Entity::OnUpdate()
{
	for (auto& component : this->mPlainComponents)
	{
		component->Update_Internal();
		component->Update();
	}
}
