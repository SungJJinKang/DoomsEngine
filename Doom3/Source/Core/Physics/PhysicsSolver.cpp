#include "PhysicsSolver.h"

#include "Collider/ColliderSolution.h"

const std::vector<const typename doom::BVHAABB3D::node_type*> doom::physics::PhysicsSolver::GetCollideBVHNodes
(
	const typename BVHAABB3D::node_type* const leafBVHNode
)
{
	D_ASSERT(leafBVHNode != nullptr && leafBVHNode->GetIsValid() == true && leafBVHNode->mIsLeaf == true);
	std::vector<const typename BVHAABB3D::node_type*> hitLeafNodeColliders;

	std::vector<const BVHAABB3D::node_type*> stack{};
	stack.push_back(leafBVHNode);

	D_ASSERT(0);

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.back();
		stack.pop_back();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			//형제 노드와 충돌하면 
		}
	}

	return hitLeafNodeColliders;
}



const std::vector<doom::physics::Collider*> doom::physics::PhysicsSolver::GetCollideCollidersHillClimb
(
	const doom::physics::Collider* const targetCollider,
	const BVHAABB3D::node_type* const targetColliderBVHNode,
	SIZE_T& stackReservationCount
)
{
	const BVHAABB3D* const ownerBVH = targetColliderBVHNode->mOwnerBVH;

	D_ASSERT(ownerBVH != nullptr);
	//D_ASSERT(leafBVHNode != nullptr && leafBVHNode->GetIsValid() == true && leafBVHNode->mIsLeaf == true);



	//First. To Find highest node collide with leafBVHNode, Hill Climb until not collide with sibling node 
	const BVHAABB3D::node_type* currentNode = targetColliderBVHNode;

	while (ownerBVH->GetIsNodeValid(currentNode) && currentNode->mIndex != currentNode->mOwnerBVH->GetRootNodeIndex())
	{
		const BVHAABB3D::node_type* const siblingNode = ownerBVH->GetSiblingNode(currentNode->mIndex);

		if (
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
}

const std::vector<doom::physics::Collider*> doom::physics::PhysicsSolver::GetCollideColliders
(
	const typename BVHAABB3D::node_type* const leafBVHNode
)
{
	D_ASSERT(leafBVHNode != nullptr && leafBVHNode->GetIsValid() == true && leafBVHNode->mIsLeaf == true);
	std::vector<doom::physics::Collider*> hitLeafNodeColliders;

	//std::stack<const BVHAABB3D::node_type*> stack{};
	//stack.push(leafBVHNode);
	D_ASSERT(0);

	return hitLeafNodeColliders;
}

const std::vector<const typename doom::BVHAABB3D::node_type*> doom::physics::PhysicsSolver::GetCollideBVHNodes
(
	const doom::BVHAABB3D* bvhTree, const doom::physics::Collider* const col, SIZE_T& stackReservationCount
)
{
	std::vector<const typename BVHAABB3D::node_type*> hitLeafNodeColliders;

	static std::vector<const BVHAABB3D::node_type*> stack{};
	stack.reserve(stackReservationCount);
	stack.push_back(bvhTree->GetRootNode());

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


const std::vector<doom::physics::Collider*> doom::physics::PhysicsSolver::GetCollideColliders
(
	const doom::BVHAABB3D* bvhTree, const doom::physics::Collider* const col, SIZE_T& stackReservationCount
)
{
	std::vector<Collider*> hitLeafNodeColliders;

	static std::vector<const BVHAABB3D::node_type*> stack{};
	stack.reserve(stackReservationCount);

	stack.push_back(bvhTree->GetRootNode());

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

const std::vector<doom::physics::Collider*> doom::physics::PhysicsSolver::GetCollideColliders
(
	const doom::BVHAABB3D* bvhTree, 
	const doom::physics::Collider* const col, 
	const BVHAABB3D::node_type* const BVHNode,
	SIZE_T& stackReservationCount)
{
	std::vector<Collider*> hitLeafNodeColliders;

	static std::vector<const BVHAABB3D::node_type*> stack{};
	stack.reserve(stackReservationCount);

	stack.push_back(bvhTree->GetRootNode());

	while (stack.empty() == false)
	{
		const BVHAABB3D::node_type* const targetNode = stack.back();
		stack.pop_back();

		if (targetNode != nullptr && targetNode->GetIsValid() == true)
		{
			if (targetNode->mIsLeaf == true)
			{//if node is world object
				if (ColliderSolution::CheckIsOverlap(&(BVHNode->mBoundingCollider), &(targetNode->mBoundingCollider)) == true)
				{
					if(ColliderSolution::CheckIsOverlap(col, targetNode->mCollider) == true)
					{
						hitLeafNodeColliders.push_back(targetNode->mCollider);
					}
				}
			}
			else
			{
				if (doom::physics::ColliderSolution::CheckIsOverlap(&(BVHNode->mBoundingCollider), &(targetNode->mBoundingCollider)) == true)
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
