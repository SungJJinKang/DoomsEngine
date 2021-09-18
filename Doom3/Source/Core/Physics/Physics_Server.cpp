#include "Physics_Server.h"

#include "Game/GameCore.h"
#include "Physics_Setting.h"

#include "Collider/ColliderSolution.h"
#include "Collider/Collider.h"

#include "PhysicsComponent/ColliderComponent.h"
#include <StaticContainer/StaticContainer.h>

#include <UserInput_Server.h>

void doom::physics::Physics_Server::UpdatePhysicsOnOff()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F11))
	{
		Physics_Setting::SetIsPhysicsOn(!Physics_Setting::GetIsPhysicsOn());
	}
}

void doom::physics::Physics_Server::LoadPhysicsSetting()
{
	Physics_Setting::SetIsPhysicsOn(static_cast<bool>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<int>("PHYSICS", "ENABLE")));

	Physics_Setting::ENLARGED_AABB2D_OFFSET = static_cast<float>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<double>("PHYSICS", "ENLARGED_AABB2D_OFFSET"));
	Physics_Setting::ENLARGED_AABB3D_OFFSET = static_cast<float>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<double>("PHYSICS", "ENLARGED_AABB3D_OFFSET"));

}

void doom::physics::Physics_Server::Init()
{
	
	LoadPhysicsSetting();
	
}


void doom::physics::Physics_Server::Update()
{
	UpdatePhysicsOnOff();

	if (Physics_Setting::GetIsPhysicsOn() == true)
	{
		mPhysicsDebugger.UpdateDebugger();
	}
}

void doom::physics::Physics_Server::FixedUpdateCollision()
{
	if (Physics_Setting::GetIsPhysicsOn() == true)
	{
		SolveColliderComponents();
	}
}



void doom::physics::Physics_Server::SolveColliderComponents()
{
	const std::vector<ColliderComponent*>& colliderComponents = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (ColliderComponent* colliderComp : colliderComponents)
	{
		colliderComp->ResetAllCollisionState();
		colliderComp->OnPreUpdatePhysics();
	}

	for (unsigned int i = 0; i < colliderComponents.size(); i++)
	{
		for (unsigned int j = i + 1; j < colliderComponents.size(); j++)
		{
			//First : Do BVH Test


			//Second : If pass BVH Test, Test Collider
			Collider* col1 = colliderComponents[i]->GetWorldCollider();
			Collider* col2 = colliderComponents[j]->GetWorldCollider();
			bool isOverlap = ColliderSolution::CheckIsOverlap(col1, col2);
			if (isOverlap)
			{
				col1->bmIsCollideAtCurrentFrame = true;
				col2->bmIsCollideAtCurrentFrame = true;
			}
		}
	}

	for (auto component : colliderComponents)
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
