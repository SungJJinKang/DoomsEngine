#include "BVH.h"

#include <stack>
#include <queue>
#include <utility>

#include "Physics/Collider/Collider.h"
#include "Physics/Collider/PhysicsGeneric.h"
#include "Physics/Collider/ColliderSolution.h"






template <typename ColliderType>
bool doom::BVH<ColliderType>::BVHRayCast(const doom::physics::Ray & ray)

{
	std::stack<int> stack{};
	stack.push(this->mTree.mRootNodeIndex);
	while (stack.empty() == false)
	{
		int index = stack.top();
		stack.pop();

		if constexpr (std::is_same_v<doom::physics::AABB2D, ColliderType> == true)
		{
			if (doom::physics::IsOverlapRayAndAABB2D(ray, this->mTree.mNodes[index].mBoundingCollider) == false)
			{// if don't hit with bounding box
				continue;
			}
		}
		else if constexpr (std::is_same_v<doom::physics::AABB3D, ColliderType> == true)
		{
			if (doom::physics::IsOverlapRayAndAABB3D(ray, this->mTree.mNodes[index].mBoundingCollider) == false)
			{// if don't hit with bounding box
				continue;
			}
		}
		else if constexpr (std::is_same_v<doom::physics::Sphere, ColliderType> == true)
		{
			if (doom::physics::IsOverlapRayAndSphere(ray, this->mTree.mNodes[index].mBoundingCollider) == false)
			{// if don't hit with bounding box
				continue;
			}
		}
		else
		{
			NEVER_HAPPEN;
		}


		if (this->mTree.mNodes[index].mIsLeaf)
		{//if node is world object

			if (physics::ColliderSolution::CheckIsOverlap(this->mTree.mNodes[index].mCollider, static_cast<physics::Collider*>(const_cast<physics::Ray*>(&ray))) == true)
			{// check collision with ray and world object collider
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			stack.push(this->mTree.mNodes[index].mLeftNode);
			stack.push(this->mTree.mNodes[index].mRightNode);
		}
	}
	return false;
}



/// <summary>
/// Find best sibling 
/// How?
/// 
/// When new leaf node is added, Pick
/// Added areas size of ancesters should be at least
/// </summary>
/// <typeparam name="ColliderType"></typeparam>
/// <param name="siblindInex"></param>
/// <param name="computedAreaSize"></param>
/// <returns></returns>
template <typename ColliderType>
int doom::BVH<ColliderType>::PickBest(const ColliderType& L)
{
	//https://github.com/selimanac/DAABBCC/blob/v2.0/daabbcc/src/DynamicTree/b2DynamicTree.cpp


	using node_priority_queue_type_t = typename std::priority_queue<NodeCost, std::vector<NodeCost>, std::greater<NodeCost>>;
	node_priority_queue_type_t queue{};
	queue.push(std::make_pair(this->mTree.mRootNodeIndex, InheritedCost(L, this->mTree.mNodes[this->mTree.mRootNodeIndex].mBoundingCollider)));

	float toInsertSurfaceArea = ColliderType::GetArea(L);
	float bestCost = math::infinity<float>();
	int bestIndex = NULL_NODE_INDEX;
	int searchIndex;
	float searchInheritedCost;

	while (queue.size() > 0)
	{
		NodeCost node = queue.top();
		queue.pop();

		searchIndex = node.first;
		searchInheritedCost = node.second;

		ColliderType& search_aabb = this->mTree.mNodes[searchIndex].mBoundingCollider;

		//Why Get UnionArea L with Ancestors  ??
		//If you want ancester's area of newly inserted node, you just be needed to compute unioned area with them
		float cost = ColliderType::GetUnionArea(L, search_aabb) + searchInheritedCost;
		if (cost < bestCost) {
			bestCost = cost;
			bestIndex = searchIndex;
		}

		//https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf 86 Page
		float inheritedCost = InheritedCost(L, search_aabb) + searchInheritedCost;
		float lowerBound = toInsertSurfaceArea + inheritedCost;

		if (lowerBound < bestCost) {
			int child1 = this->mTree.mNodes[searchIndex].mLeftNode;
			int child2 = this->mTree.mNodes[searchIndex].mRightNode;
			if (child1 != NULL_NODE_INDEX) {
				assert(child2 != NULL_NODE_INDEX);
				queue.emplace(child1, inheritedCost);
				queue.emplace(child2, inheritedCost);
			}
		}
	}

	return bestIndex;
}

template<typename ColliderType>
int doom::BVH<ColliderType>::AllocateNewNode()
{
	int newNodeIndex;
	if (this->mTree.freedNodeIndexList.empty() == false)
	{// if there is freedNode
		newNodeIndex = this->mTree.freedNodeIndexList.front();
		this->mTree.freedNodeIndexList.pop();
	}
	else
	{
		this->mTree.mCurrentAllocatedNodeCount++;

		D_ASSERT(this->mTree.mCurrentAllocatedNodeCount <= this->mTree.mNodeCapacity);
		
		newNodeIndex = this->mTree.mCurrentAllocatedNodeCount - 1;
	}

	this->mTree.mCurrentActiveNodeCount++;

	this->mTree.mNodes[newNodeIndex].mIndex = newNodeIndex;
	this->mTree.mNodes[newNodeIndex].bmIsActive = true;

	return newNodeIndex;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::AllocateLeafNode(const ColliderType& boundingCollider, physics::Collider* collider)
{
	int newNodexIndex = this->AllocateNewNode();
	auto& newNode = this->mTree.mNodes[newNodexIndex];

	newNode.mOwnerBVH = this;
	//newNode.mBoundingCollider = collider;
	newNode.mBoundingCollider = boundingCollider;
	newNode.mEnlargedBoundingCollider = ColliderType::EnlargeAABB(newNode.mBoundingCollider);

	newNode.mCollider = collider;
	newNode.mIsLeaf = true;

	return newNode.mIndex;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::AllocateInternalNode()
{
	int newNodexIndex = this->AllocateNewNode();
	auto& newNode = this->mTree.mNodes[newNodexIndex];

	newNode.mOwnerBVH = this;

	newNode.mIsLeaf = false;

	return newNode.mIndex;
}


template<typename ColliderType>
void doom::BVH<ColliderType>::FreeNode(int nodeIndex)
{
	D_ASSERT(nodeIndex != NULL_NODE_INDEX);
	
	this->mTree.mNodes[nodeIndex].Clear();

	this->mTree.mCurrentActiveNodeCount--;
	this->mTree.freedNodeIndexList.push(nodeIndex);
}

template <typename ColliderType>
int doom::BVH<ColliderType>::GetSibling(int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	int parentIndex = this->mTree.mNodes[index].mParentIndex;
	
	if (parentIndex == NULL_NODE_INDEX)
	{
		return NULL_NODE_INDEX;
	}

	if (this->mTree.mNodes[parentIndex].mLeftNode == index)
	{
		return this->mTree.mNodes[parentIndex].mRightNode;
	}
	else if (this->mTree.mNodes[parentIndex].mRightNode == index)
	{
		return this->mTree.mNodes[parentIndex].mLeftNode;
	}
	else
	{
		NEVER_HAPPEN;
	}
}

template <typename ColliderType>
bool doom::BVH<ColliderType>::IsHasChild(int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	return (this->mTree.mNodes[index].mLeftNode != NULL_NODE_INDEX) || (this->mTree.mNodes[index].mRightNode != NULL_NODE_INDEX);
}

template <typename ColliderType>
typename doom::BVH<ColliderType>::node_view_type doom::BVH<ColliderType>::InsertLeaf(const ColliderType& L, physics::Collider* collider)
{
	int newObjectLeafIndex = AllocateLeafNode(L, collider);
	if (this->mTree.mCurrentActiveNodeCount == 1)
	{// if allocate first node, this->mTree.mNodes.size() will be 1
		this->mTree.mRootNodeIndex = newObjectLeafIndex;
	}
	else
	{
		int bestSibling = PickBest(L);

		/*
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; ++i)
		{
			if (this->mTree.mNodes[i].bmIsActive == true)
			{
				
			}
		}
		*/

		int oldParentIndex = this->mTree.mNodes[bestSibling].mParentIndex;
		int newParentIndex = AllocateInternalNode();
		this->mTree.mNodes[newParentIndex].mParentIndex = oldParentIndex;
		this->mTree.mNodes[newParentIndex].mBoundingCollider = ColliderType::Union(L, this->mTree.mNodes[bestSibling].mBoundingCollider);
		this->mTree.mNodes[newParentIndex].mEnlargedBoundingCollider = ColliderType::EnlargeAABB(this->mTree.mNodes[newParentIndex].mBoundingCollider);

		if (oldParentIndex != NULL_NODE_INDEX)
		{
			if (this->mTree.mNodes[oldParentIndex].mLeftNode == bestSibling)
			{
				this->mTree.mNodes[oldParentIndex].mLeftNode = newParentIndex;
			}
			else
			{
				this->mTree.mNodes[oldParentIndex].mRightNode = newParentIndex;
			}

			this->mTree.mNodes[newParentIndex].mLeftNode = bestSibling;
			this->mTree.mNodes[newParentIndex].mRightNode = newObjectLeafIndex;
			this->mTree.mNodes[bestSibling].mParentIndex = newParentIndex;
			this->mTree.mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
		}
		else
		{
			this->mTree.mNodes[newParentIndex].mLeftNode = bestSibling;
			this->mTree.mNodes[newParentIndex].mRightNode = newObjectLeafIndex;
			this->mTree.mNodes[bestSibling].mParentIndex = newParentIndex;
			this->mTree.mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
			this->mTree.mRootNodeIndex = newParentIndex;

		}


		HillClimingReconstruct(this->mTree.mNodes[newObjectLeafIndex].mParentIndex);
	}

	return this->MakeBVH_Node_View(newObjectLeafIndex);
}

template <typename ColliderType>
typename doom::BVH<ColliderType>::node_view_type doom::BVH<ColliderType>::UpdateLeafNode(int targetLeafNodeIndex, bool force)
{
	D_ASSERT(targetLeafNodeIndex != NULL_NODE_INDEX);

	node_type* targetLeafNode = this->GetNode(targetLeafNodeIndex);

	D_ASSERT(targetLeafNode->mIsLeaf == true);

	if (ColliderType::CheckIsCompletlyEnclosed(targetLeafNode->mBoundingCollider, targetLeafNode->mEnlargedBoundingCollider) == false || force == true)
	{
		D_DEBUG_LOG("Update Leaf Node!!!", eLogType::D_ALWAYS);
		//we will remove node and re-insert node
		//you don't need reset mEnlargedBoundingCollider at here
		this->RemoveLeafNode(targetLeafNode);
		return this->InsertLeaf(targetLeafNode->mBoundingCollider, targetLeafNode->mCollider);
	}
	else
	{
		return this->MakeBVH_Node_View(targetLeafNodeIndex);
	}
}

/// <summary>
/// When union with new boundingCollider,
/// How much is ColliderType larger than before
/// 
/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf 77p
/// SA mean area of boundingCollider
/// 세모SA(Node) = SA(Node U L) - SA(Node)  -----> 한 AABB에서 새 AABB를 합치면 얼만큼 Area가 추가되는지
/// </summary>
/// <typeparam name="ColliderType"></typeparam>
/// <param name="L"></param>
/// <param name="candidate"></param>
/// <returns></returns>
template <typename ColliderType>
float doom::BVH<ColliderType>::InheritedCost(const ColliderType& L, const ColliderType& candidate)
{
	return ColliderType::GetUnionArea(L, candidate) - ColliderType::GetArea(candidate);
}

template <typename ColliderType>
void doom::BVH<ColliderType>::HillClimingReconstruct(int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	while (index != NULL_NODE_INDEX)
	{
		D_ASSERT(this->mTree.mNodes[index].mLeftNode != NULL_NODE_INDEX && this->mTree.mNodes[index].mRightNode != NULL_NODE_INDEX);

		this->ReConstructNodeAABB(index);
		index = Balance(index); // TODO : Balancing만 하면 이상해진다.

		index = this->mTree.mNodes[index].mParentIndex;
	}
}

/// <summary>
/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf 117 page
/// 
/// Only when inbalance, balance it
/// return newNodeIndex at passed lowerNodeIndex position
/// Really Really fast
/// 
/// We just need reconstruct only boundingCollider of imbalancedLowerNodeIndex's parent
/// </summary>
/// <typeparam name="ColliderType"></typeparam>
/// <param name="nodeAIndex"></param>
/// <param name="nodeBIndex"></param>
template <typename ColliderType>
int doom::BVH<ColliderType>::Balance(int lowerNodeIndex)
{
	if (this->IsHasChild(lowerNodeIndex) == false)
	{
		return lowerNodeIndex;
	}

	int parentIndexOfLowerNode = this->mTree.mNodes[lowerNodeIndex].mParentIndex;
	if (parentIndexOfLowerNode == NULL_NODE_INDEX)
	{
		return lowerNodeIndex;
	}
	int siblingIndexOfParentOfLowerNode = this->GetSibling(parentIndexOfLowerNode);
	if (siblingIndexOfParentOfLowerNode == NULL_NODE_INDEX)
	{
		return lowerNodeIndex;
	}

	/*
	if (this->IsHasChild(siblingIndexOfParentOfLowerNode) == true)
	{
		return lowerNodeIndex;
	}
	*/
	int higerNodeIndex = siblingIndexOfParentOfLowerNode;

	int siblingIndexOfLowerNode = this->GetSibling(lowerNodeIndex);
	if (ColliderType::GetArea(this->mTree.mNodes[parentIndexOfLowerNode].mBoundingCollider) < ColliderType::GetUnionArea(this->mTree.mNodes[siblingIndexOfLowerNode].mBoundingCollider, this->mTree.mNodes[higerNodeIndex].mBoundingCollider))
	{// when SA(parent of lowernode) < SA(sibling of lowerNode U upperNode), don't rotate 
		return lowerNodeIndex;
	}
	


	D_ASSERT(higerNodeIndex != NULL_NODE_INDEX);
	D_ASSERT(lowerNodeIndex != NULL_NODE_INDEX);

	int parentIndexOfimbalancedHigherNode = this->mTree.mNodes[higerNodeIndex].mParentIndex;
	int parentIndexOfimbalancedLowerNodeIndex = this->mTree.mNodes[lowerNodeIndex].mParentIndex;

	if (this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mLeftNode == higerNodeIndex)
	{
		if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mLeftNode = lowerNodeIndex;
		}
		else if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mLeftNode = lowerNodeIndex;
		}
	}
	else if (this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mRightNode == higerNodeIndex)
	{
		if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mRightNode = lowerNodeIndex;
		}
		else if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mRightNode = lowerNodeIndex;
		}
	}
	else
	{
		NEVER_HAPPEN;
	}

	this->mTree.mNodes[higerNodeIndex].mParentIndex = parentIndexOfimbalancedLowerNodeIndex;
	this->mTree.mNodes[lowerNodeIndex].mParentIndex = parentIndexOfimbalancedHigherNode;

	ReConstructNodeAABB(this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mIndex);
	return higerNodeIndex;
}

template<typename ColliderType>
void doom::BVH<ColliderType>::RemoveLeafNode(int targetLeafNodeIndex)
{
	if (targetLeafNodeIndex == NULL_NODE_INDEX)
	{
		return;
	}

	auto nodePointer = this->GetNode(targetLeafNodeIndex);
	if (nodePointer != nullptr)
	{
		this->RemoveLeafNode(nodePointer);
	}
}

template<typename ColliderType>
void doom::BVH<ColliderType>::RemoveLeafNode(doom::BVH<ColliderType>::node_type* targetLeafNode)
{
	if (targetLeafNode == nullptr)
	{
		return;
	}

	int targetLeafNodeIndex = targetLeafNode->mIndex;

	D_ASSERT(this->mTree.mNodes[targetLeafNodeIndex].mIsLeaf == true);

	int parentIndex = this->mTree.mNodes[targetLeafNodeIndex].mParentIndex;
	int grandParentIndex = NULL_NODE_INDEX;
	int siblingIndex = NULL_NODE_INDEX;

	if (parentIndex != NULL_NODE_INDEX)
	{
		grandParentIndex = this->mTree.mNodes[parentIndex].mParentIndex;
		if (this->mTree.mNodes[parentIndex].mLeftNode == targetLeafNodeIndex)
		{
			siblingIndex = this->mTree.mNodes[parentIndex].mRightNode;
		}
		else if (this->mTree.mNodes[parentIndex].mRightNode == targetLeafNodeIndex)
		{
			siblingIndex = this->mTree.mNodes[parentIndex].mLeftNode;
		}
		else
		{
			NEVER_HAPPEN;
		}

		if (grandParentIndex == NULL_NODE_INDEX)
		{
			int originalRootNodeIndex = this->mTree.mRootNodeIndex;

			D_ASSERT(this->mTree.mRootNodeIndex == this->mTree.mNodes[siblingIndex].mParentIndex);
			this->mTree.mRootNodeIndex = siblingIndex;
			this->mTree.mNodes[siblingIndex].mParentIndex = NULL_NODE_INDEX;

			this->FreeNode(originalRootNodeIndex);
		}
		else
		{
			if (this->mTree.mNodes[grandParentIndex].mLeftNode == parentIndex)
			{
				this->mTree.mNodes[grandParentIndex].mLeftNode = siblingIndex;
			}
			else if (this->mTree.mNodes[grandParentIndex].mRightNode == parentIndex)
			{
				this->mTree.mNodes[grandParentIndex].mRightNode = siblingIndex;
			}
			else
			{
				NEVER_HAPPEN;
			}

			int originalParentIindex = this->mTree.mNodes[siblingIndex].mParentIndex;
			this->mTree.mNodes[siblingIndex].mParentIndex = grandParentIndex;
			this->FreeNode(originalParentIindex);
			HillClimingReconstruct(grandParentIndex);
		}
	}
	else
	{//when target leaf node is root node
		this->mTree.mRootNodeIndex = NULL_NODE_INDEX;
	}
	

	this->FreeNode(targetLeafNodeIndex);
}

template<typename ColliderType>
void doom::BVH<ColliderType>::ReConstructNodeAABB(int targetNodeIndex)
{
	if (this->mTree.mNodes[targetNodeIndex].mIsLeaf == true)
	{
		return;
	}

	D_ASSERT(this->mTree.mNodes[targetNodeIndex].mLeftNode != NULL_NODE_INDEX && this->mTree.mNodes[targetNodeIndex].mRightNode != NULL_NODE_INDEX);
	this->mTree.mNodes[targetNodeIndex].mBoundingCollider = ColliderType::Union(this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mLeftNode].mBoundingCollider, this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mRightNode].mBoundingCollider);
	this->mTree.mNodes[targetNodeIndex].mEnlargedBoundingCollider = ColliderType::EnlargeAABB(this->mTree.mNodes[targetNodeIndex].mBoundingCollider);
}



float additionalWeight(float x, float l)
{
	return x + math::lerp(0, x > 0 ? 1 : -1, math::abs(l));
}


/// <summary>
/// We will get sum of Internal Nodes's area
/// 
/// Less sum of Internal Nodes's area -> More fast Ray cast
/// </summary>
/// <typeparam name="ColliderType"></typeparam>
/// <returns></returns>
template <typename ColliderType>
float doom::BVH<ColliderType>::ComputeCost()
{
	float cost{ 0.0f };
	for (int i = 0 ; i < this->mTree.mCurrentAllocatedNodeCount; i++)
	{
		if (this->mTree.mNodes[i].mIsLeaf == false)
		{
			cost += ColliderType::GetArea(this->mTree.mNodes[i].mBoundingCollider);
		}
	}
	return cost;
}



template <typename ColliderType>
int doom::BVH<ColliderType>::GetHeight(int index, int& longestHeight, int currentHeight)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	
	currentHeight++;
	if (currentHeight > longestHeight)
	{
		longestHeight = currentHeight;
	}

	if (this->mTree.mNodes[index].mLeftNode != NULL_NODE_INDEX)
	{
		GetHeight(this->mTree.mNodes[index].mLeftNode, longestHeight, currentHeight);
	}

	if (this->mTree.mNodes[index].mRightNode != NULL_NODE_INDEX)
	{
		GetHeight(this->mTree.mNodes[index].mRightNode, longestHeight, currentHeight);
	}
	return longestHeight;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::GetDepth(int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);

	int depth{ 0 };
	int parentIndex{ this->mTree.mNodes[index].mParentIndex };
	while (parentIndex != NULL_NODE_INDEX)
	{
		parentIndex = this->mTree.mNodes[index].mParentIndex;
		depth++;
	}
	return depth;
}

template<typename ColliderType>
typename doom::BVH<ColliderType>::node_type* doom::BVH<ColliderType>::GetNode(int nodeIndex)
{
	D_ASSERT(nodeIndex >= 0);
	D_ASSERT(this->mTree.mNodes[nodeIndex].bmIsActive == true);

	return &(this->mTree.mNodes[nodeIndex]);
}


template <typename ColliderType>
int doom::BVH<ColliderType>::GetLeafNodeCount()
{
	int count{ 0 };
	for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
	{
		if (this->mTree.mNodes[i].mIsLeaf == true)
		{
			count++;
		}
	}
	return count;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::GetLeaf(int index)
{
	int count = 0;
	for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
	{
		auto& node = this->mTree.mNodes[i];
		if (node.bmIsActive == true && node.mIsLeaf == true)
		{
			if (index == count)
			{
				return i;
			}
			
			count++;
		}
	}

	return NULL_NODE_INDEX;
}

template<typename ColliderType>
bool doom::BVH<ColliderType>::IsAncesterOf(int ancesterIndex, int decesterIndex)
{
	int index = this->mTree.mNodes[decesterIndex].mParentIndex;
	while (index != NULL_NODE_INDEX)
	{
		if (ancesterIndex == index)
		{
			return true;
		}

		index = this->mTree.mNodes[index].mParentIndex;
	}
	return false;
}





template class doom::BVH<doom::physics::AABB2D>;
template class doom::BVH<doom::physics::AABB3D>;
template class doom::BVH<doom::physics::Sphere>;
