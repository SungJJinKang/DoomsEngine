#include "Entity.h"
#include "../../Component/Transform.h"

Doom::Entity::Entity() : _EntityName{}, _Transform{}, Components{}
{
	Doom::Transform* tr = this->AddComponent<Doom::Transform>();
	tr->_Transform = tr;
	this->_Transform = tr;
}