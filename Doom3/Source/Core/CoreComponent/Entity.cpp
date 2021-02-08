#include "Entity.h"

#include "../../Component/Transform.h"
#include"World.h"

using namespace doom;

Entity::Entity(Entity* parent) : mEntityName{}, mPlainComponents{}, mParent{ parent }, mChilds{}
{
	this->mTransform = this->AddComponent<Transform>();
}

Entity::~Entity()
{
	this->ClearComponents();
}

std::string_view Entity::GetEntityName() const
{
	return this->mEntityName;
}

Transform* Entity::GetTransform() const
{
	return this->mTransform;
}

void Entity::Destroy()
{
	//Work Flow : World::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	World::GetCurrentWorld().DestroyEntity(*this);
	
}

void Entity::OnUpdate()
{
	for (auto& component : this->mPlainComponents)
	{
		component->Update_Internal();
		component->Update();
	}
}
