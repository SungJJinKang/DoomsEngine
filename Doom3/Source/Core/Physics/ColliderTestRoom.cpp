#include "ColliderTestRoom.h"

void doom::physics::ColliderTestRoom::FixedUpdatePhysics()
{

}

void doom::physics::ColliderTestRoom::AddTestCollider(Collider* collider)
{
	this->mTestColliders.push_back(collider);
}
