#include "Physics_Server.h"

#include "PhysicsComponent/ColliderComponent.h"
#include <StaticContainer/StaticContainer.h>

void doom::physics::Physics_Server::Init()
{

}


void doom::physics::Physics_Server::Update()
{
	this->mColliderTestRoom.DrawDebug();
}

void doom::physics::Physics_Server::FixedUpdateCollision()
{
#ifdef DEBUG_MODE
	this->mColliderTestRoom.FixedUpdatePhysics();
#endif
	auto componentPair = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (unsigned int i = 0; i < componentPair.second; i++)
	{
		componentPair.first[i]->OnPreUpdatePhysics();
	}
	for (unsigned int i = 0; i < componentPair.second; i++)
	{
		componentPair.first[i]->UpdatePhysics();
	}
	for (unsigned int i = 0; i < componentPair.second; i++)
	{
		componentPair.first[i]->OnPostUpdatePhysics();
	}
}

void doom::physics::Physics_Server::OnEndOfFrame()
{

}

