#include "Physics_Server.h"

#include "Game/GameCore.h"
#include "Physics_Setting.h"

#include "Collider/ColliderSolution.h"
#include "Collider/Collider.h"

#include "Physics_Setting.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <PhysicsComponent/Rigidbody/Rigidbody.h>
#include <Misk/StaticContainer/StaticContainer.h>

#include "PhysicsSolver.h"
#include <Physics/Debugger/PhysicsDebugger.h>


void dooms::physics::Physics_Server::LoadPhysicsSetting()
{
	Physics_Setting::SetIsPhysicsOn(static_cast<bool>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<INT32>("PHYSICS", "ENABLE")));

	Physics_Setting::ENLARGED_AABB2D_OFFSET = static_cast<FLOAT32>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<FLOAT64>("PHYSICS", "ENLARGED_AABB2D_OFFSET"));
	Physics_Setting::ENLARGED_AABB3D_OFFSET = static_cast<FLOAT32>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<FLOAT64>("PHYSICS", "ENLARGED_AABB3D_OFFSET"));

}

dooms::physics::Physics_Server::~Physics_Server()
{
	dooms::StaticContainer<Rigidbody>::ClearContainer();
	dooms::StaticContainer<ColliderComponent>::ClearContainer();
}

void dooms::physics::Physics_Server::Init(const int argc, char* const* const argv)
{
	
	LoadPhysicsSetting();
	
}


void dooms::physics::Physics_Server::Update()
{
	if (Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER == true)
	{
		PhysicsDebugger::UpdateDebugger();
	}
}

void dooms::physics::Physics_Server::FixedUpdate()
{
	D_START_PROFILING(FixedUpdateCollision, eProfileLayers::CPU);
	FixedUpdateCollision();
	D_END_PROFILING(FixedUpdateCollision);
	
}

void dooms::physics::Physics_Server::FixedUpdateCollision()
{
	if (Physics_Setting::GetIsPhysicsOn() == true)
	{
		ResetCollisionData();
		SolveColliderComponents();
	}
}


void dooms::physics::Physics_Server::ResetCollisionData()
{
	const std::vector<ColliderComponent*>& colliderComponents = dooms::StaticContainer<ColliderComponent>::GetAllStaticComponents();

	D_START_PROFILING(Physics_Server_SolveColliderComponents_ResetAllCollisionState, eProfileLayers::CPU);
	for (ColliderComponent* colliderComp : colliderComponents)
	{
		colliderComp->OnPreUpdatePhysics();
	}
	
	const std::vector<Rigidbody*>& rigidbodyComponents = dooms::StaticContainer<Rigidbody>::GetAllStaticComponents();
	for (Rigidbody* const rigidbodyComponent : rigidbodyComponents)
	{
		rigidbodyComponent->ClearCollideCollidersAtFrame();
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_ResetAllCollisionState);
}

void dooms::physics::Physics_Server::SolveColliderComponents()
{
	const std::vector<Rigidbody*>& rigidbodyComponents = dooms::StaticContainer<Rigidbody>::GetAllStaticComponents();
	
	size_t stackReservationCount = 1;
	
	D_START_PROFILING(Physics_Server_SolveColliderComponents_SolveCollision, eProfileLayers::CPU);
	for (Rigidbody* const rigidbodyComponent : rigidbodyComponents)
	{
		const std::vector<ColliderComponent*>& attachedColliderComponents = rigidbodyComponent->GetAttachedColliderComponents();
		for(ColliderComponent* const colliderComponent : attachedColliderComponents)
		{
			Collider* const testedCollider = colliderComponent->GetWorldCollider();

			//const std::vector<dooms::physics::Collider*> hitBVHLeafNodes = dooms::physics::PhysicsSolver::GetCollideColliders(&mPhysicsColliderBVH, testedCollider, stackReservationCount);

			const std::vector<dooms::physics::Collider*> hitBVHLeafNodes = dooms::physics::PhysicsSolver::GetCollideColliders
			(
				&mPhysicsColliderBVH,
				testedCollider,
				colliderComponent->BVH_AABB3D_Node_Object::mBVH_Node_View.GetNode(),
				stackReservationCount
			);

			
			for (dooms::physics::Collider* leafNodeCollider : hitBVHLeafNodes)
			{
				if (testedCollider != leafNodeCollider)
				{
					rigidbodyComponent->AddCollideCollidersAtFrame(leafNodeCollider);
				}
			}

		}
		
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_SolveCollision);


	D_START_PROFILING(Physics_Server_SolveColliderComponents_OnPostUpdatePhysics, eProfileLayers::CPU);
	for (const Rigidbody* const rigidbodyComponent : rigidbodyComponents)
	{
		const std::vector<ColliderComponent*>& attachedColliderComponents = rigidbodyComponent->GetAttachedColliderComponents();
		for (ColliderComponent* colliderComponent : attachedColliderComponents)
		{
			colliderComponent->OnPostUpdatePhysics();
		}
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_OnPostUpdatePhysics);

}

void dooms::physics::Physics_Server::OnEndOfFrame()
{

}

void dooms::physics::Physics_Server::QueryCollision()
{
}
