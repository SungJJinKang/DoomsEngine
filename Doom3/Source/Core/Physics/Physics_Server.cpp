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
	if (bmIsPhysicsOn == false)
	{
		return;
	}

#ifdef DEBUG_MODE
	mColliderTestRoom.DrawDebug();

	if (userinput::UserInput_Server::GetKeyToggle(userinput::eKEY_CODE::KEY_F11))
	{
		DrawDebugColliderComponents();
	}

	if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F1) == true)
	{
		const std::vector<ColliderComponent*>& components = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
		for (auto component : components)
		{
			component->UpdateWorldColliderCache(true);
			component->DrawWorldColliderCache();
		}
	}
	
#endif
}

void doom::physics::Physics_Server::FixedUpdateCollision()
{
	if (bmIsPhysicsOn == false)
	{
		return;
	}

#ifdef DEBUG_MODE
	mColliderTestRoom.FixedUpdatePhysics();
#endif
	SolveColliderComponents();

}

#ifdef DEBUG_MODE
void doom::physics::Physics_Server::DrawDebugColliderComponents()
{
	const std::vector<ColliderComponent*>& components = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (auto component : components)
	{
		component->GetWorldCollider()->DrawPhysicsDebug();
	}
}
#endif

void doom::physics::Physics_Server::SolveColliderComponents()
{
	const std::vector<ColliderComponent*>& components = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (auto component : components)
	{
		component->ResetAllCollisionState();
		component->OnPreUpdatePhysics();
	}

	for (unsigned int i = 0; i < components.size(); i++)
	{
		for (unsigned int j = i + 1; j < components.size(); j++)
		{
			//First : Do BVH Test


			//Second : If pass BVH Test, Test Collider
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
