#include "Physics_Server.h"

#include "Game/GameCore.h"
#include "Physics_Setting.h"

#include "Collider/ColliderSolution.h"
#include "Collider/Collider.h"

#include "PhysicsComponent/ColliderComponent.h"
#include <StaticContainer/StaticContainer.h>

#include "PhysicsSolver.h"


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
	
	if (Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER == true)
	{
		mPhysicsDebugger.UpdateDebugger();
	}
}

void doom::physics::Physics_Server::FixedUpdate()
{
	D_START_PROFILING(FixedUpdateCollision, eProfileLayers::CPU);
	FixedUpdateCollision();
	D_END_PROFILING(FixedUpdateCollision);
	
}

void doom::physics::Physics_Server::FixedUpdateCollision()
{
	if (Physics_Setting::GetIsPhysicsOn() == true)
	{
		ResetCollisionData();
		SolveColliderComponents();
	}
}


void doom::physics::Physics_Server::ResetCollisionData()
{
	const std::vector<ColliderComponent*>& colliderComponents = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();

	D_START_PROFILING(Physics_Server_SolveColliderComponents_ResetAllCollisionState, eProfileLayers::CPU);
	for (ColliderComponent* colliderComp : colliderComponents)
	{
		colliderComp->ResetAllCollisionState();
		colliderComp->OnPreUpdatePhysics();
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_ResetAllCollisionState);
}

void doom::physics::Physics_Server::SolveColliderComponents()
{
	

	const std::vector<ColliderComponent*>& colliderComponents = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();
	
	size_t stackReservationCount = 1;


	//TODO : Implement Solve Collide based on BVH Tree
	D_START_PROFILING(Physics_Server_SolveColliderComponents_SolveCollision, eProfileLayers::CPU);
	for (unsigned int i = 0; i < colliderComponents.size(); i++)
	{
		Collider* const testedCollider = colliderComponents[i]->GetWorldCollider();

		//const std::vector<doom::physics::Collider*> hitBVHLeafNodes = doom::physics::PhysicsSolver::GetCollideColliders(&mPhysicsColliderBVH, testedCollider, stackReservationCount);
		
		const std::vector<doom::physics::Collider*> hitBVHLeafNodes = doom::physics::PhysicsSolver::GetCollideColliders
		(
			&mPhysicsColliderBVH,
			testedCollider, 
			colliderComponents[i]->BVH_AABB3D_Node_Object::mBVH_Node_View.GetNode(),
			stackReservationCount
		);
		

		bool isCollideWithAnyCollider = false;
		for (doom::physics::Collider* leafNodeCollider : hitBVHLeafNodes)
		{
			if (testedCollider != leafNodeCollider)
			{
				leafNodeCollider->bmIsCollideAtCurrentFrame = true;
				isCollideWithAnyCollider = true;
			}
		
		}

		if (isCollideWithAnyCollider == true)
		{
			testedCollider->bmIsCollideAtCurrentFrame = true;
		}
		
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_SolveCollision);


	D_START_PROFILING(Physics_Server_SolveColliderComponents_OnPostUpdatePhysics, eProfileLayers::CPU);
	for (auto component : colliderComponents)
	{
		component->OnPostUpdatePhysics();
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_OnPostUpdatePhysics);

}

void doom::physics::Physics_Server::OnEndOfFrame()
{

}

void doom::physics::Physics_Server::QueryCollision()
{
}
