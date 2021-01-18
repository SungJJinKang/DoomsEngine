#include "Component.h"
#include "../Core/CoreComponent/Entity.h"

void Doom::Component::InitComponent(Entity& entity)
{
	this->_OwnerEntity = &entity;
	this->_Transform = &(entity.Transform());
	
	this->isAddedToEntity = true;
}
