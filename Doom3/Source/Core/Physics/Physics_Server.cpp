#include "Physics_Server.h"

#include "Collider/ColliderSolution.h"
#include "Collider/Collider.h"

#include "PhysicsComponent/ColliderComponent.h"
#include <StaticContainer/StaticContainer.h>

#include <UserInput_Server.h>

void doom::physics::Physics_Server::Init()
{

}


void doom::physics::Physics_Server::Update()
{
#ifdef DEBUG_MODE
	this->mColliderTestRoom.DrawDebug();
	ONLY_WHEN_KEY_TOGGLE_ON(userinput::eKEY_CODE::KEY_F11, this->DrawDebugColliderComponents());
#endif
}

void doom::physics::Physics_Server::FixedUpdateCollision()
{
#ifdef DEBUG_MODE
	this->mColliderTestRoom.FixedUpdatePhysics();
#endif
	SolveColliderComponents();

}

void doom::physics::Physics_Server::DrawDebugColliderComponents()
{
	auto components = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (auto component : components)
	{
		component->GetWorldCollider()->DrawPhysicsDebug();
	}
}

void doom::physics::Physics_Server::SolveColliderComponents()
{
	auto components = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (auto component : components)
	{
		component->OnPreUpdatePhysics();
	}

	for (unsigned int i = 0; i < components.size(); i++)
	{
		for (unsigned int j = i + 1; j < components.size(); j++)
		{
			Collider* col1 = components[i]->GetWorldCollider();
			Collider* col2 = components[j]->GetWorldCollider();
			bool isOverlap = ColliderSolution::CheckIsOverlap(col1, col2);
			if (isOverlap)
			{
				col1->bmIsCollision = true;
				col2->bmIsCollision = true;
			}
		}
	}

	for (auto component : components)
	{
		component->OnPostUpdatePhysics();
	}
}

void doom::physics::Physics_Server::OnEndOfFrame()
{

}

void doom::physics::Physics_Server::QueryCollision()
{
}
