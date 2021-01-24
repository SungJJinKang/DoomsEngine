#include "Entity.h"
#include "../../Component/Transform.h"

doom::Entity::Entity() : _EntityName{}, _Transform{}, Components{}
{
	doom::Transform* tr = this->AddComponent<doom::Transform>();
	tr->_Transform = tr;
	this->_Transform = tr;
}