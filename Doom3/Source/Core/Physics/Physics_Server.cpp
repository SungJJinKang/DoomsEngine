#include "Physics_Server.h"

#include "Game/GameCore.h"
#include "Physics_Setting.h"

#include "Collider/ColliderSolution.h"
#include "Collider/Collider.h"

#include "PhysicsComponent/ColliderComponent.h"
#include <StaticContainer/StaticContainer.h>


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
		SolveColliderComponents();
	}
}





void doom::physics::Physics_Server::SolveColliderComponents()
{
	const std::vector<ColliderComponent*>& colliderComponents = doom::StaticContainer<ColliderComponent>::GetAllStaticComponents();

	D_START_PROFILING(Physics_Server_SolveColliderComponents_ResetAllCollisionState, eProfileLayers::CPU);
	for (ColliderComponent* colliderComp : colliderComponents)
	{
		colliderComp->ResetAllCollisionState();
		colliderComp->OnPreUpdatePhysics();
	}
	D_END_PROFILING(Physics_Server_SolveColliderComponents_ResetAllCollisionState);

	size_t stackReservationCount = 1;


	//TODO : Implement Solve Collide based on BVH Tree
	D_START_PROFILING(Physics_Server_SolveColliderComponents_SolveCollision, eProfileLayers::CPU);
	for (unsigned int i = 0; i < colliderComponents.size(); i++)
	{
		Collider* const testedCollider = colliderComponents[i]->GetWorldCollider();

		//const std::vector<doom::physics::Collider*> hitBVHLeafNodes = GetCollideColliders(testedCollider, stackReservationCount);
		const std::vector<doom::physics::Collider*> hitBVHLeafNodes = GetCollideCollidersHillClimb
		(
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

const std::vector<const typename doom::BVHAABB3D::node_type*> doom::physics::Physics_Server::GetCollideBVHNodes
(
	const typename BVHAABB3D::node_type* const leafBVHNode
) const
{
	D_ASSERT(leafBVHNode != nullptr && leafBVHNode->GetIsValid() == true && leafBVHNode->mIsLeaf == true);
	std::vector<const typename BVHAABB3D::node_type*> hitLeafNodeColliders;

	std::vector<const BVHAABB3D::node_type*> stack{};
	stack.push_back(leafBVHNode);

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.back();
		stack.pop_back();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			//형제 노드와 충돌하면 
		}
	}
}



const std::vector<doom::physics::Collider*> doom::physics::Physics_Server::GetCollideCollidersHillClimb
(
	const doom::physics::Collider* const targetCollider, 
	const BVHAABB3D::node_type* const targetColliderBVHNode,
	size_t& stackReservationCount
) const
{
	const BVHAABB3D* const ownerBVH = targetColliderBVHNode->mOwnerBVH;

	D_ASSERT(ownerBVH != nullptr);
	D_ASSERT(leafBVHNode != nullptr && leafBVHNode->GetIsValid() == true && leafBVHNode->mIsLeaf == true);

	
	
	//First. To Find highest node collide with leafBVHNode, Hill Climb until not collide with sibling node 
	const BVHAABB3D::node_type* currentNode = targetColliderBVHNode;

	while(ownerBVH->GetIsNodeValid(currentNode) && currentNode->mIndex != currentNode->mOwnerBVH->GetRootNodeIndex())
	{
		const BVHAABB3D::node_type* const siblingNode = ownerBVH->GetSiblingNode(currentNode->mIndex);

		if(
			ownerBVH->GetIsNodeValid(siblingNode) == false
			||
			ColliderSolution::CheckIsOverlap(&(currentNode->mBoundingCollider), &(siblingNode->mBoundingCollider)) == false
			)
		{
			//If don't collide with sibling, break;
			break;
		}
		
		currentNode = currentNode->GetParentNode();
	}

	std::vector<Collider*> hitLeafNodeColliders;

	static std::vector<const BVHAABB3D::node_type*> stack{};
	stack.reserve(stackReservationCount);
	stack.push_back(currentNode);

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.back();
		stack.pop_back();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			if (targetNode->mIsLeaf == true)
			{//if node is world object
				doom::physics::Collider* const leafNodeCollider = targetNode->mCollider;
				if (ColliderSolution::CheckIsOverlap(targetCollider, leafNodeCollider) == true)
				{
					hitLeafNodeColliders.push_back(leafNodeCollider);
				}
			}
			else
			{
				stack.push_back(targetNode->GetLeftChildNode());
				stack.push_back(targetNode->GetRightChildNode());
			}

		}
	}

	stackReservationCount = stackReservationCount > stack.capacity() ? stackReservationCount : stack.capacity();

	stack.clear();

	return hitLeafNodeColliders;

	return hitLeafNodeColliders;
}

const std::vector<doom::physics::Collider*> doom::physics::Physics_Server::GetCollideColliders
(
	const typename BVHAABB3D::node_type* const leafBVHNode
) const
{
	D_ASSERT(leafBVHNode != nullptr && leafBVHNode->GetIsValid() == true && leafBVHNode->mIsLeaf == true);
	std::vector<doom::physics::Collider*> hitLeafNodeColliders;

	//std::stack<const BVHAABB3D::node_type*> stack{};
	//stack.push(leafBVHNode);


}

const std::vector<const typename doom::BVHAABB3D::node_type*> doom::physics::Physics_Server::GetCollideBVHNodes
(
	const doom::physics::Collider* const col, size_t& stackReservationCount
) const
{
	std::vector<const typename BVHAABB3D::node_type*> hitLeafNodeColliders;

	static std::vector<const BVHAABB3D::node_type*> stack{};
	stack.reserve(stackReservationCount);
	stack.push_back(mPhysicsColliderBVH.GetRootNode());

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.back();
		stack.pop_back();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			if (targetNode->mIsLeaf == true)
			{//if node is world object
				doom::physics::Collider* const leafNodeCollider = targetNode->mCollider;
				if (ColliderSolution::CheckIsOverlap(col, leafNodeCollider) == true)
				{
					hitLeafNodeColliders.push_back(targetNode);
				}
			}
			else
			{
				if (doom::physics::ColliderSolution::CheckIsOverlap(col, &(targetNode->mBoundingCollider)) == true)
				{
					stack.push_back(targetNode->GetLeftChildNode());
					stack.push_back(targetNode->GetRightChildNode());
				}
			}

		}
	}

	stackReservationCount = stackReservationCount > stack.capacity() ? stackReservationCount : stack.capacity();

	stack.clear();

	return hitLeafNodeColliders;
}


const std::vector<doom::physics::Collider*> doom::physics::Physics_Server::GetCollideColliders
(
	const doom::physics::Collider* const col, size_t& stackReservationCount
) const
{
	std::vector<Collider*> hitLeafNodeColliders;

	static std::vector<const BVHAABB3D::node_type*> stack{};
	stack.reserve(stackReservationCount);

	stack.push_back(mPhysicsColliderBVH.GetRootNode());
	
	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.back();
		stack.pop_back();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			if (targetNode->mIsLeaf == true)
			{//if node is world object
				doom::physics::Collider* const leafNodeCollider = targetNode->mCollider;
				if (ColliderSolution::CheckIsOverlap(col, leafNodeCollider) == true)
				{
					hitLeafNodeColliders.push_back(leafNodeCollider);
				}
			}
			else
			{
				if (doom::physics::ColliderSolution::CheckIsOverlap(col, &(targetNode->mBoundingCollider)) == true)
				{
					stack.push_back(targetNode->GetLeftChildNode());
					stack.push_back(targetNode->GetRightChildNode());
				}
			}
			
		}
	} 
	
	stackReservationCount = stackReservationCount > stack.capacity() ? stackReservationCount : stack.capacity();

	stack.clear();

	return hitLeafNodeColliders;
}

void doom::physics::Physics_Server::OnEndOfFrame()
{

}

void doom::physics::Physics_Server::QueryCollision()
{
}
