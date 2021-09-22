#include "BVH.h"

#include <stack>
#include <queue>
#include <utility>

#include "Physics/Collider/Collider.h"
#include "Physics/Collider/PhysicsGeneric.h"
#include "Physics/Collider/ColliderSolution.h"



template <typename ColliderType>
doom::BVH<ColliderType>::BVH(const int nodeCapacity)
	:mNodeCapacity{ nodeCapacity }
{
	mNodes = new BVH_Node<ColliderType>[mNodeCapacity];
}

template <typename ColliderType>
doom::BVH<ColliderType>::~BVH()
{
	delete[] mNodes;
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
FORCE_INLINE int doom::BVH<ColliderType>::PickBest(const ColliderType& L)
{
	//https://github.com/selimanac/DAABBCC/blob/v2.0/daabbcc/src/DynamicTree/b2DynamicTree.cpp


	using node_priority_queue_type_t = typename std::priority_queue<NodeCost, std::vector<NodeCost>, std::greater<NodeCost>>;
	node_priority_queue_type_t queue{};
	queue.push(std::make_pair(mRootNodeIndex, InheritedCost(L, mNodes[mRootNodeIndex].mBoundingCollider)));

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

		ColliderType& search_aabb = mNodes[searchIndex].mBoundingCollider;

		//Why Get UnionArea L with Ancestors  ??
		//If you want ancester's area of newly inserted node, you just be needed to compute unioned area with them
		float cost = ColliderType::GetUnionArea(L, search_aabb) + searchInheritedCost;
		if (cost <= bestCost) {
			bestCost = cost;
			bestIndex = searchIndex;
		}

		//https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf 86 Page
		float inheritedCost = InheritedCost(L, search_aabb) + searchInheritedCost;
		float lowerBound = toInsertSurfaceArea + inheritedCost;

		if (lowerBound < bestCost) {
			int child1 = mNodes[searchIndex].mLeftNode;
			int child2 = mNodes[searchIndex].mRightNode;
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
FORCE_INLINE int doom::BVH<ColliderType>::AllocateNewNode()
{
	int newNodeIndex;
	if (freedNodeIndexList.empty() == false)
	{// if there is freedNode
		newNodeIndex = freedNodeIndexList.front();
		freedNodeIndexList.pop();
	}
	else
	{
		mCurrentAllocatedNodeCount++;

		D_ASSERT(mCurrentAllocatedNodeCount <= mNodeCapacity);
		
		newNodeIndex = mCurrentAllocatedNodeCount - 1;
	}

	mCurrentActiveNodeCount++;

	mNodes[newNodeIndex].Clear();
	mNodes[newNodeIndex].mOwnerBVH = this;
	mNodes[newNodeIndex].mIndex = newNodeIndex;
	mNodes[newNodeIndex].bmIsActive = true;

	return newNodeIndex;
}

template <typename ColliderType>
FORCE_INLINE int doom::BVH<ColliderType>::AllocateLeafNode(const ColliderType& boundingCollider, physics::Collider* collider)
{
	int newNodexIndex = AllocateNewNode();
	auto& newNode = mNodes[newNodexIndex];

	//newNode.mBoundingCollider = collider;
	newNode.mBoundingCollider = boundingCollider;
	newNode.mEnlargedBoundingCollider = ColliderType::EnlargeAABB(newNode.mBoundingCollider);

	newNode.mCollider = collider;
	newNode.mIsLeaf = true;

	return newNode.mIndex;
}

template <typename ColliderType>
FORCE_INLINE int doom::BVH<ColliderType>::AllocateInternalNode()
{
	int newNodexIndex = AllocateNewNode();
	auto& newNode = mNodes[newNodexIndex];

	newNode.mIsLeaf = false;

	return newNode.mIndex;
}


template<typename ColliderType>
FORCE_INLINE void doom::BVH<ColliderType>::FreeNode(int nodeIndex)
{
	D_ASSERT(nodeIndex != NULL_NODE_INDEX);
	
	mCurrentActiveNodeCount--;
	freedNodeIndexList.push(nodeIndex);
}

template<typename ColliderType>
FORCE_INLINE typename doom::BVH<ColliderType>::node_type* doom::BVH<ColliderType>::GetRootNode()
{
	return GetNode(mRootNodeIndex);
}

template<typename ColliderType>
FORCE_INLINE const typename doom::BVH<ColliderType>::node_type* doom::BVH<ColliderType>::GetRootNode() const
{
	return GetNode(mRootNodeIndex);
}

template<typename ColliderType>
FORCE_INLINE int doom::BVH<ColliderType>::GetRootNodeIndex() const
{
	return mRootNodeIndex;
}

template <typename ColliderType>
FORCE_INLINE int doom::BVH<ColliderType>::GetSibling(const int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	int parentIndex = mNodes[index].mParentIndex;
	
	if (parentIndex == NULL_NODE_INDEX)
	{
		return NULL_NODE_INDEX;
	}

	if (mNodes[parentIndex].mLeftNode == index)
	{
		return mNodes[parentIndex].mRightNode;
	}
	else if (mNodes[parentIndex].mRightNode == index)
	{
		return mNodes[parentIndex].mLeftNode;
	}
	else
	{
		NEVER_HAPPEN;
	}
}

template <typename ColliderType>
FORCE_INLINE bool doom::BVH<ColliderType>::IsHasChild(const int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	return (mNodes[index].mLeftNode != NULL_NODE_INDEX) || (mNodes[index].mRightNode != NULL_NODE_INDEX);
}

template <typename ColliderType>
FORCE_INLINE typename doom::BVH<ColliderType>::node_view_type doom::BVH<ColliderType>::InsertLeaf(const ColliderType& L, physics::Collider* collider)
{
	int newObjectLeafIndex = AllocateLeafNode(L, collider);
	if (mCurrentActiveNodeCount == 1)
	{// if allocate first node, mNodes.size() will be 1
		mRootNodeIndex = newObjectLeafIndex;
	}
	else
	{
		int bestSibling = PickBest(L);

		/*
		for (int i = 0; i < mCurrentAllocatedNodeCount; ++i)
		{
			if (mNodes[i].bmIsActive == true)
			{
				
			}
		}
		*/

		int oldParentIndex = mNodes[bestSibling].mParentIndex;
		int newParentIndex = AllocateInternalNode();
		mNodes[newParentIndex].mParentIndex = oldParentIndex;
		mNodes[newParentIndex].mBoundingCollider = ColliderType::Union(L, mNodes[bestSibling].mBoundingCollider);
		mNodes[newParentIndex].mEnlargedBoundingCollider = ColliderType::EnlargeAABB(mNodes[newParentIndex].mBoundingCollider);

		if (oldParentIndex != NULL_NODE_INDEX)
		{
			if (mNodes[oldParentIndex].mLeftNode == bestSibling)
			{
				mNodes[oldParentIndex].mLeftNode = newParentIndex;
			}
			else
			{
				mNodes[oldParentIndex].mRightNode = newParentIndex;
			}

			mNodes[newParentIndex].mLeftNode = bestSibling;
			mNodes[newParentIndex].mRightNode = newObjectLeafIndex;
			mNodes[bestSibling].mParentIndex = newParentIndex;
			mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
		}
		else
		{
			mNodes[newParentIndex].mLeftNode = bestSibling;
			mNodes[newParentIndex].mRightNode = newObjectLeafIndex;
			mNodes[bestSibling].mParentIndex = newParentIndex;
			mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
			mRootNodeIndex = newParentIndex;

		}


		HillClimingReconstruct(mNodes[newObjectLeafIndex].mParentIndex);
	}

	return MakeBVH_Node_View(newObjectLeafIndex);
}

template <typename ColliderType>
FORCE_INLINE typename doom::BVH<ColliderType>::node_view_type doom::BVH<ColliderType>::UpdateLeafNode(const int targetLeafNodeIndex, const bool force)
{
	D_ASSERT(targetLeafNodeIndex != NULL_NODE_INDEX);

	node_type* const targetLeafNode = GetNode(targetLeafNodeIndex);

	D_ASSERT(targetLeafNode->mIsLeaf == true);

	if (force == true || ColliderType::CheckIsCompletlyEnclosed(targetLeafNode->mBoundingCollider, targetLeafNode->mEnlargedBoundingCollider) == false)
	{
		//we will remove node and re-insert node
		//you don't need reset mEnlargedBoundingCollider at here
		RemoveLeafNode(targetLeafNode);
		return InsertLeaf(targetLeafNode->mBoundingCollider, targetLeafNode->mCollider);
	}
	else
	{
		return MakeBVH_Node_View(targetLeafNodeIndex);
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
FORCE_INLINE float doom::BVH<ColliderType>::InheritedCost(const ColliderType& L, const ColliderType& candidate)
{
	return ColliderType::GetUnionArea(L, candidate) - ColliderType::GetArea(candidate);
}

template <typename ColliderType>
FORCE_INLINE void doom::BVH<ColliderType>::HillClimingReconstruct(int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	while (index != NULL_NODE_INDEX)
	{
		D_ASSERT(mNodes[index].mLeftNode != NULL_NODE_INDEX && mNodes[index].mRightNode != NULL_NODE_INDEX);

		ReConstructNodeAABB(index);
		index = Balance(index); // TODO : Balancing만 하면 이상해진다.

		index = mNodes[index].mParentIndex;
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
FORCE_INLINE int doom::BVH<ColliderType>::Balance(int lowerNodeIndex)
{
	if (IsHasChild(lowerNodeIndex) == false)
	{
		return lowerNodeIndex;
	}

	int parentIndexOfLowerNode = mNodes[lowerNodeIndex].mParentIndex;
	if (parentIndexOfLowerNode == NULL_NODE_INDEX)
	{
		return lowerNodeIndex;
	}
	int siblingIndexOfParentOfLowerNode = GetSibling(parentIndexOfLowerNode);
	if (siblingIndexOfParentOfLowerNode == NULL_NODE_INDEX)
	{
		return lowerNodeIndex;
	}

	/*
	if (IsHasChild(siblingIndexOfParentOfLowerNode) == true)
	{
		return lowerNodeIndex;
	}
	*/
	int higerNodeIndex = siblingIndexOfParentOfLowerNode;

	int siblingIndexOfLowerNode = GetSibling(lowerNodeIndex);
	if (ColliderType::GetArea(mNodes[parentIndexOfLowerNode].mBoundingCollider) < ColliderType::GetUnionArea(mNodes[siblingIndexOfLowerNode].mBoundingCollider, mNodes[higerNodeIndex].mBoundingCollider))
	{// when SA(parent of lowernode) < SA(sibling of lowerNode U upperNode), don't rotate 
		return lowerNodeIndex;
	}
	


	D_ASSERT(higerNodeIndex != NULL_NODE_INDEX);
	D_ASSERT(lowerNodeIndex != NULL_NODE_INDEX);

	int parentIndexOfimbalancedHigherNode = mNodes[higerNodeIndex].mParentIndex;
	int parentIndexOfimbalancedLowerNodeIndex = mNodes[lowerNodeIndex].mParentIndex;

	if (mNodes[parentIndexOfimbalancedHigherNode].mLeftNode == higerNodeIndex)
	{
		if (mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode == lowerNodeIndex)
		{
			mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode = higerNodeIndex;
			mNodes[parentIndexOfimbalancedHigherNode].mLeftNode = lowerNodeIndex;
		}
		else if (mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode == lowerNodeIndex)
		{
			mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode = higerNodeIndex;
			mNodes[parentIndexOfimbalancedHigherNode].mLeftNode = lowerNodeIndex;
		}
	}
	else if (mNodes[parentIndexOfimbalancedHigherNode].mRightNode == higerNodeIndex)
	{
		if (mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode == lowerNodeIndex)
		{
			mNodes[parentIndexOfimbalancedLowerNodeIndex].mLeftNode = higerNodeIndex;
			mNodes[parentIndexOfimbalancedHigherNode].mRightNode = lowerNodeIndex;
		}
		else if (mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode == lowerNodeIndex)
		{
			mNodes[parentIndexOfimbalancedLowerNodeIndex].mRightNode = higerNodeIndex;
			mNodes[parentIndexOfimbalancedHigherNode].mRightNode = lowerNodeIndex;
		}
	}
	else
	{
		NEVER_HAPPEN;
	}

	mNodes[higerNodeIndex].mParentIndex = parentIndexOfimbalancedLowerNodeIndex;
	mNodes[lowerNodeIndex].mParentIndex = parentIndexOfimbalancedHigherNode;

	ReConstructNodeAABB(mNodes[parentIndexOfimbalancedLowerNodeIndex].mIndex);
	return higerNodeIndex;
}

template<typename ColliderType>
FORCE_INLINE void doom::BVH<ColliderType>::RemoveLeafNode(int targetLeafNodeIndex)
{
	if (targetLeafNodeIndex != NULL_NODE_INDEX)
	{
		auto nodePointer = GetNode(targetLeafNodeIndex);
		if (nodePointer != nullptr)
		{
			RemoveLeafNode(nodePointer);
		}
	}

	
}

template<typename ColliderType>
FORCE_INLINE void doom::BVH<ColliderType>::RemoveLeafNode(doom::BVH<ColliderType>::node_type* targetLeafNode)
{
	if (targetLeafNode != nullptr)
	{

		int targetLeafNodeIndex = targetLeafNode->mIndex;

		D_ASSERT(mNodes[targetLeafNodeIndex].mIsLeaf == true);

		int parentIndex = mNodes[targetLeafNodeIndex].mParentIndex;
		int grandParentIndex = NULL_NODE_INDEX;
		int siblingIndex = NULL_NODE_INDEX;

		if (parentIndex != NULL_NODE_INDEX)
		{
			grandParentIndex = mNodes[parentIndex].mParentIndex;
			if (mNodes[parentIndex].mLeftNode == targetLeafNodeIndex)
			{
				siblingIndex = mNodes[parentIndex].mRightNode;
			}
			else if (mNodes[parentIndex].mRightNode == targetLeafNodeIndex)
			{
				siblingIndex = mNodes[parentIndex].mLeftNode;
			}
			else
			{
				NEVER_HAPPEN;
			}

			if (grandParentIndex == NULL_NODE_INDEX)
			{
				int originalRootNodeIndex = mRootNodeIndex;

				D_ASSERT(mRootNodeIndex == mNodes[siblingIndex].mParentIndex);
				mRootNodeIndex = siblingIndex;
				mNodes[siblingIndex].mParentIndex = NULL_NODE_INDEX;

				FreeNode(originalRootNodeIndex);
			}
			else
			{
				if (mNodes[grandParentIndex].mLeftNode == parentIndex)
				{
					mNodes[grandParentIndex].mLeftNode = siblingIndex;
				}
				else if (mNodes[grandParentIndex].mRightNode == parentIndex)
				{
					mNodes[grandParentIndex].mRightNode = siblingIndex;
				}
				else
				{
					NEVER_HAPPEN;
				}

				int originalParentIindex = mNodes[siblingIndex].mParentIndex;
				mNodes[siblingIndex].mParentIndex = grandParentIndex;
				FreeNode(originalParentIindex);
				HillClimingReconstruct(grandParentIndex);
			}
		}
		else
		{//when target leaf node is root node
			mRootNodeIndex = NULL_NODE_INDEX;
		}


		FreeNode(targetLeafNodeIndex);
	}

}

template<typename ColliderType>
FORCE_INLINE void doom::BVH<ColliderType>::ReConstructNodeAABB(int targetNodeIndex)
{
	if (mNodes[targetNodeIndex].mIsLeaf == false)
	{
		D_ASSERT(mNodes[targetNodeIndex].mLeftNode != NULL_NODE_INDEX && mNodes[targetNodeIndex].mRightNode != NULL_NODE_INDEX);
		mNodes[targetNodeIndex].mBoundingCollider = ColliderType::Union(mNodes[mNodes[targetNodeIndex].mLeftNode].mBoundingCollider, mNodes[mNodes[targetNodeIndex].mRightNode].mBoundingCollider);
		mNodes[targetNodeIndex].mEnlargedBoundingCollider = ColliderType::EnlargeAABB(mNodes[targetNodeIndex].mBoundingCollider);
	}

	
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
	for (int i = 0 ; i < mCurrentAllocatedNodeCount; i++)
	{
		if (mNodes[i].mIsLeaf == false)
		{
			cost += ColliderType::GetArea(mNodes[i].mBoundingCollider);
		}
	}
	return cost;
}



template <typename ColliderType>
int doom::BVH<ColliderType>::GetHeight(const int index, int& longestHeight, int currentHeight)
{
	D_ASSERT(index != NULL_NODE_INDEX);
	
	currentHeight++;
	if (currentHeight > longestHeight)
	{
		longestHeight = currentHeight;
	}

	if (mNodes[index].mLeftNode != NULL_NODE_INDEX)
	{
		GetHeight(mNodes[index].mLeftNode, longestHeight, currentHeight);
	}

	if (mNodes[index].mRightNode != NULL_NODE_INDEX)
	{
		GetHeight(mNodes[index].mRightNode, longestHeight, currentHeight);
	}
	return longestHeight;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::GetDepth(const int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);

	int depth{ 0 };
	int parentIndex{ mNodes[index].mParentIndex };
	while (parentIndex != NULL_NODE_INDEX)
	{
		parentIndex = mNodes[index].mParentIndex;
		depth++;
	}
	return depth;
}

template<typename ColliderType>
typename doom::BVH<ColliderType>::node_type* doom::BVH<ColliderType>::GetNode(const int nodeIndex)
{
	D_ASSERT(GetIsNodeValid(nodeIndex) == true);

	return &(mNodes[nodeIndex]);
}

template<typename ColliderType>
const typename doom::BVH<ColliderType>::node_type* doom::BVH<ColliderType>::GetNode(const int nodeIndex) const
{
	D_ASSERT(GetIsNodeValid(nodeIndex) == true);

	return &(mNodes[nodeIndex]);
}

template<typename ColliderType>
bool doom::BVH<ColliderType>::GetIsNodeValid(const int nodeIndex) const
{
	return nodeIndex >= 0 && mNodes[nodeIndex].bmIsActive == true;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::GetLeafNodeCount()
{
	int count{ 0 };
	for (int i = 0; i < mCurrentAllocatedNodeCount; i++)
	{
		if (mNodes[i].mIsLeaf == true)
		{
			count++;
		}
	}
	return count;
}

template <typename ColliderType>
int doom::BVH<ColliderType>::GetLeaf(const int index)
{
	int targetLeafNodeIndex = NULL_NODE_INDEX;

	int count = 0;
	for (int nodeIndex = 0; nodeIndex < mCurrentAllocatedNodeCount; nodeIndex++)
	{
		auto& node = mNodes[nodeIndex];
		if (node.bmIsActive == true && node.mIsLeaf == true)
		{
			if (index == count)
			{
				targetLeafNodeIndex = nodeIndex;
				break;
			}
			
			count++;
		}
	}

	return targetLeafNodeIndex;
}

template<typename ColliderType>
bool doom::BVH<ColliderType>::IsAncesterOf(const int ancesterIndex, const int decesterIndex)
{
	bool isAncester = false;

	int index = mNodes[decesterIndex].mParentIndex;
	while (index != NULL_NODE_INDEX)
	{
		if (ancesterIndex == index)
		{
			isAncester = true;
			break;
		}

		index = mNodes[index].mParentIndex;
	}

	return isAncester;
}





template class doom::BVH<doom::physics::AABB2D>;
template class doom::BVH<doom::physics::AABB3D>;
template class doom::BVH<doom::physics::Sphere>;
