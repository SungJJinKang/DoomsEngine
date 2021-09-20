#include "Physics_Server.h"

#include "Game/GameCore.h"
#include "Physics_Setting.h"

#include "Collider/ColliderSolution.h"
#include "Collider/Collider.h"

#include "PhysicsComponent/ColliderComponent.h"
#include <StaticContainer/StaticContainer.h>

#include <UserInput_Server.h>
#include <stack>

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
		//First : Do BVH Test

		/*
		Collider* const testedCollider = colliderComponents[i]->GetWorldCollider();
		const std::vector<doom::physics::Collider*> hitBVHLeafNodes = GetCollideColliders(testedCollider);

		bool isCollideWithAnyCollider = false;
		for (doom::physics::Collider* leafNodeCollider : hitBVHLeafNodes)
		{
			leafNodeCollider->bmIsCollideAtCurrentFrame = true;
			isCollideWithAnyCollider = true;
		}

		if (isCollideWithAnyCollider == true)
		{
			testedCollider->bmIsCollideAtCurrentFrame = true;
		}
		*/
	}

	for (auto component : colliderComponents)
	{
		component->OnPostUpdatePhysics();
	}
}

const std::vector<const typename BVHAABB3D::node_type*> doom::physics::Physics_Server::GetCollideBVHNodes(const doom::physics::Collider* const col) const
{
	std::vector<const typename BVHAABB3D::node_type*> hitLeafNodeColliders;

	std::stack<const BVHAABB3D::node_type*> stack{};
	stack.push(mPhysicsColliderBVH.GetRootNode());

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.top();
		stack.pop();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			if (targetNode->GetIsLeafNode() == true)
			{//if node is world object
				doom::physics::Collider* const leafNodeCollider = targetNode->GetCollider();
				if (ColliderSolution::CheckIsOverlap(col, leafNodeCollider) == true)
				{
					hitLeafNodeColliders.push_back(targetNode);
				}
			}
			else
			{
				if (doom::physics::ColliderSolution::CheckIsOverlap(col, &(targetNode->GetBoundingCollider())) == true)
				{
					stack.push(targetNode->GetLeftChildNode());
					stack.push(targetNode->GetRightChildNode());
				}
			}

		}
	}
	return hitLeafNodeColliders;
}


const std::vector<doom::physics::Collider*> doom::physics::Physics_Server::GetCollideColliders(const doom::physics::Collider* const col) const
{
	std::vector<Collider*> hitLeafNodeColliders;

	std::stack<const BVHAABB3D::node_type*> stack{};
	stack.push(mPhysicsColliderBVH.GetRootNode());

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.top();
		stack.pop();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			if (targetNode->GetIsLeafNode() == true)
			{//if node is world object
				doom::physics::Collider* const leafNodeCollider = targetNode->GetCollider();
				if (ColliderSolution::CheckIsOverlap(col, leafNodeCollider) == true)
				{
					hitLeafNodeColliders.push_back(leafNodeCollider);
				}
			}
			else
			{
				if (doom::physics::ColliderSolution::CheckIsOverlap(col, &(targetNode->GetBoundingCollider())) == true)
				{
					stack.push(targetNode->GetLeftChildNode());
					stack.push(targetNode->GetRightChildNode());
				}
			}
			
		}
	}
	return hitLeafNodeColliders;
}

void doom::physics::Physics_Server::OnEndOfFrame()
{

}

void doom::physics::Physics_Server::QueryCollision()
{
}
