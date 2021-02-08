#include "Component.h"
#include "../Core/CoreComponent/Entity.h"
#include "Transform.h"

using namespace doom;






Component::Component() : bIsAddedToEntity{}, mOwnerEntity{}, mTransform{}, mIsActivated{}
{

}

Component::~Component() // Never put parameter to component Destructor (including derived class)
{

}

void Component::Init_Internal(Entity& entity)
{
	D_ASSERT(bIsAddedToEntity == false);
	mOwnerEntity = &entity;
	mTransform = entity.GetTransform();
	bIsAddedToEntity = true;

}

doom::Entity* Component::GetOwnerEntity()
{
	return this->mOwnerEntity;
}

doom::Transform* Component::GetTransform()
{
	return this->mTransform;
}

