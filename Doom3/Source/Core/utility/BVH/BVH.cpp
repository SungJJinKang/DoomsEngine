#include "BVH.h"

#include <stack>
#include <queue>
#include <type_traits>
#include <utility>

#ifdef DEBUG_MODE
#include <vector>
#include <unordered_set>
#endif

#include "Physics/Collider/Collider.h"
#include "Physics/Collider/PhysicsGeneric.h"
#include "Physics/Collider/ColliderSolution.h"

#include "../../Graphics/DebugGraphics.h"

#include "Graphics/Graphics_Server.h"
#include "Graphics/GraphicsAPI.h"
#include "Game/AssetManager/AssetManager.h"
#include "Graphics/Material.h"

#ifdef DEBUG_MODE
#include <vector_erase_move_lastelement/vector_swap_erase.h>
#endif


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
			stack.push(this->mTree.mNodes[index].mChild1);
			stack.push(this->mTree.mNodes[index].mChild2);
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
			int child1 = this->mTree.mNodes[searchIndex].mChild1;
			int child2 = this->mTree.mNodes[searchIndex].mChild2;
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

#ifdef DEBUG_MODE
	recentAddedLeaf.push(newNode.mIndex);
#endif

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

	if (this->mTree.mNodes[parentIndex].mChild1 == index)
	{
		return this->mTree.mNodes[parentIndex].mChild2;
	}
	else if (this->mTree.mNodes[parentIndex].mChild2 == index)
	{
		return this->mTree.mNodes[parentIndex].mChild1;
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
	return (this->mTree.mNodes[index].mChild1 != NULL_NODE_INDEX) || (this->mTree.mNodes[index].mChild2 != NULL_NODE_INDEX);
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
			if (this->mTree.mNodes[oldParentIndex].mChild1 == bestSibling)
			{
				this->mTree.mNodes[oldParentIndex].mChild1 = newParentIndex;
			}
			else
			{
				this->mTree.mNodes[oldParentIndex].mChild2 = newParentIndex;
			}

			this->mTree.mNodes[newParentIndex].mChild1 = bestSibling;
			this->mTree.mNodes[newParentIndex].mChild2 = newObjectLeafIndex;
			this->mTree.mNodes[bestSibling].mParentIndex = newParentIndex;
			this->mTree.mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
		}
		else
		{
			this->mTree.mNodes[newParentIndex].mChild1 = bestSibling;
			this->mTree.mNodes[newParentIndex].mChild2 = newObjectLeafIndex;
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
		D_ASSERT(this->mTree.mNodes[index].mChild1 != NULL_NODE_INDEX && this->mTree.mNodes[index].mChild2 != NULL_NODE_INDEX);

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

	if (this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mChild1 == higerNodeIndex)
	{
		if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild1 == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild1 = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mChild1 = lowerNodeIndex;
		}
		else if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild2 == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild2 = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mChild1 = lowerNodeIndex;
		}
	}
	else if (this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mChild2 == higerNodeIndex)
	{
		if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild1 == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild1 = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mChild2 = lowerNodeIndex;
		}
		else if (this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild2 == lowerNodeIndex)
		{
			this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mChild2 = higerNodeIndex;
			this->mTree.mNodes[parentIndexOfimbalancedHigherNode].mChild2 = lowerNodeIndex;
		}
	}
	else
	{
		NEVER_HAPPEN;
	}

	this->mTree.mNodes[higerNodeIndex].mParentIndex = parentIndexOfimbalancedLowerNodeIndex;
	this->mTree.mNodes[lowerNodeIndex].mParentIndex = parentIndexOfimbalancedHigherNode;

	ReConstructNodeAABB(this->mTree.mNodes[parentIndexOfimbalancedLowerNodeIndex].mIndex);

	D_DEBUG_LOG("Balance!!", eLogType::D_ALWAYS);

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
		if (this->mTree.mNodes[parentIndex].mChild1 == targetLeafNodeIndex)
		{
			siblingIndex = this->mTree.mNodes[parentIndex].mChild2;
		}
		else if (this->mTree.mNodes[parentIndex].mChild2 == targetLeafNodeIndex)
		{
			siblingIndex = this->mTree.mNodes[parentIndex].mChild1;
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
			if (this->mTree.mNodes[grandParentIndex].mChild1 == parentIndex)
			{
				this->mTree.mNodes[grandParentIndex].mChild1 = siblingIndex;
			}
			else if (this->mTree.mNodes[grandParentIndex].mChild2 == parentIndex)
			{
				this->mTree.mNodes[grandParentIndex].mChild2 = siblingIndex;
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

	D_ASSERT(this->mTree.mNodes[targetNodeIndex].mChild1 != NULL_NODE_INDEX && this->mTree.mNodes[targetNodeIndex].mChild2 != NULL_NODE_INDEX);
	this->mTree.mNodes[targetNodeIndex].mBoundingCollider = ColliderType::Union(this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mChild1].mBoundingCollider, this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mChild2].mBoundingCollider);
	this->mTree.mNodes[targetNodeIndex].mEnlargedBoundingCollider = ColliderType::EnlargeAABB(this->mTree.mNodes[targetNodeIndex].mBoundingCollider);
}

#define DebugBVHTreeOffsetX 0.1f
#define DebugBVHTreeOffsetY 0.1f

float additionalWeight(float x, float l)
{
	return x + math::lerp(0, x > 0 ? 1 : -1, math::abs(l));
}

template <typename ColliderType>
void doom::BVH<ColliderType>::DebugBVHTree(node_type* node, float x, float y, int depth)
{
	if (node == nullptr)
	{
		return;
	}

	float offsetX = static_cast<float>(1.0f / (math::pow(2, depth + 1)));
	if (node->mChild1 != NULL_NODE_INDEX)
	{
		graphics::DebugGraphics::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x - offsetX, y - DebugBVHTreeOffsetY, 0 }, this->mTree.mNodes[node->mChild1].mIsLeaf == false ? eColor::Black : ((doom::BVH<ColliderType>::recentAddedLeaf.empty() == false && doom::BVH<ColliderType>::recentAddedLeaf.top() == node->mChild1) ? eColor::Red : eColor::Blue), true);
		DebugBVHTree(&(this->mTree.mNodes[node->mChild1]), x - offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
	if (node->mChild2 != NULL_NODE_INDEX)
	{
		graphics::DebugGraphics::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x + offsetX, y - DebugBVHTreeOffsetY, 0 }, this->mTree.mNodes[node->mChild2].mIsLeaf == false ? eColor::Black : ((doom::BVH<ColliderType>::recentAddedLeaf.empty() == false && doom::BVH<ColliderType>::recentAddedLeaf.top() == node->mChild2) ? eColor::Red : eColor::Blue), true);
		DebugBVHTree(&(this->mTree.mNodes[node->mChild2]), x + offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
}

template<typename ColliderType>
void doom::BVH<ColliderType>::TreeDebug()
{
	if (this->mTree.mRootNodeIndex != NULL_NODE_INDEX)
	{
		/*
		for (int i = 0; i < this->mTree.mNodeCapacity; i++)
		{
			this->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebug(); // TODO : Draw recursively, don't draw all nodes
		}
		*/

		if (static_cast<bool>(this->mPIPForDebug))
		{
			this->mPIPForDebug->BindFrameBuffer();

			graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			this->mPIPForDebug->ClearFrameBuffer();

			graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

			DebugBVHTree(&(this->mTree.mNodes[this->mTree.mRootNodeIndex]), 0, 1, 0);

			graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
			this->mPIPForDebug->RevertFrameBuffer();
		}
	}
}

template<typename ColliderType>
void doom::BVH<ColliderType>::AABBDebug()
{
	if (static_cast<bool>(this->mPIPForDebug))
	{
		this->mPIPForDebug->BindFrameBuffer();

		graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		this->mPIPForDebug->ClearFrameBuffer();

		graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

	
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true)
			{
				if (this->recentAddedLeaf.empty() == false && i == this->recentAddedLeaf.top())
				{
					this->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Red, true);
				}
				else if (this->recentAddedLeaf.empty() == false && this->IsAncesterOf(i, this->recentAddedLeaf.top()))
				{
					this->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Blue, true);
				}
				else if(this->mTree.mNodes[i].mIsLeaf == false)
				{
					this->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Black, true);
				}
				else if (this->mTree.mNodes[i].mIsLeaf == true)
				{
					this->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Green, true);
				}
				
			}
		}
	

		graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
		this->mPIPForDebug->RevertFrameBuffer();
	}
}
template<typename ColliderType>
void doom::BVH<ColliderType>::AABBDebug(int targetNode)
{
	if (static_cast<bool>(this->mPIPForDebug))
	{
		this->mPIPForDebug->BindFrameBuffer();

		graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		this->mPIPForDebug->ClearFrameBuffer();

		graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

		/*
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true)
			{
				this->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Black, true);
			}
		}
		*/

		int index = targetNode;
		while (index != NULL_NODE_INDEX)
		{
			this->mTree.mNodes[index].mBoundingCollider.DrawPhysicsDebugColor(eColor::Red, true);
			index = this->mTree.mNodes[index].mParentIndex;
		}


		graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
		this->mPIPForDebug->RevertFrameBuffer();
	}
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
void doom::BVH<ColliderType>::InitializeDebugging()
{
	if (static_cast<bool>(this->mPIPForDebug) == false)
	{
		this->mPIPForDebug = std::make_unique<graphics::PicktureInPickture>(1024, 1024, math::Vector2(-1.0f, -1.0f), math::Vector2(1.0f, 1.0f));
		graphics::Graphics_Server::GetSingleton()->AddAutoDrawedPIPs(*(this->mPIPForDebug.get()));
	}

	if (static_cast<bool>(this->mBVHDebugMaterial) == false)
	{
		this->mBVHDebugMaterial = std::make_unique<graphics::Material>( doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("Default2DColorShader.glsl"));
	}
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

	if (this->mTree.mNodes[index].mChild1 != NULL_NODE_INDEX)
	{
		GetHeight(this->mTree.mNodes[index].mChild1, longestHeight, currentHeight);
	}

	if (this->mTree.mNodes[index].mChild2 != NULL_NODE_INDEX)
	{
		GetHeight(this->mTree.mNodes[index].mChild2, longestHeight, currentHeight);
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

template<typename ColliderType>
void doom::BVH<ColliderType>::CheckActiveNode(node_type* node, std::vector<int>& activeNodeList)
{
	if (node == nullptr)
	{
		return;
	}

#ifdef DEBUG_MODE
	if (node->bmIsActive == true)
	{
		auto iter = std::vector_find_swap_erase(activeNodeList, node->mIndex);
	}

	if (node->mChild1 != NULL_NODE_INDEX)
	{
		CheckActiveNode(&(this->mTree.mNodes[node->mChild1]), activeNodeList);
	}

	if (node->mChild2 != NULL_NODE_INDEX)
	{
		CheckActiveNode(&(this->mTree.mNodes[node->mChild2]), activeNodeList);
	}
#endif
}


template<typename ColliderType>
void doom::BVH<ColliderType>::ValidCheck()
{
#ifdef DEBUG_MODE
	if (this->mTree.mRootNodeIndex != NULL_NODE_INDEX)
	{
		//first check : recursively traverse all active nodes from rootIndex, Every active nodes in mTree.mNodes array should be traversed
		//				every active nodes in mTree.mNodes should be checked
		//				And call Node::ValidCheck();
		std::vector<int> checkedIndexs{};
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true)
			{
				checkedIndexs.push_back(i);
			}
		}
		D_ASSERT(checkedIndexs.size() == this->mTree.mCurrentActiveNodeCount);
		CheckActiveNode(&(this->mTree.mNodes[this->mTree.mRootNodeIndex]), checkedIndexs);
		D_ASSERT(checkedIndexs.size() == 0);

		//second check : traverse from each Leaf Nodes to RootNode. Check if Traversing arrived at mTree.rootIndex
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true && this->mTree.mNodes[i].mIsLeaf == true)
			{
				int index{ i };
				bool isSuccess{ false };
				while (index != NULL_NODE_INDEX)
				{
					if (index == this->mTree.mRootNodeIndex)
					{
						isSuccess = true;
						break;
					}

					index = this->mTree.mNodes[index].mParentIndex;
				}

				D_ASSERT(isSuccess == true);
			}
		}


		//third check : check all internal nodes must have 2 child,  all leaf nodes must have no child
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true)
			{
				if (this->mTree.mNodes[i].mIsLeaf == false)
				{// leaf node must have 2 child
					D_ASSERT(this->mTree.mNodes[i].mChild1 != NULL_NODE_INDEX && this->mTree.mNodes[i].mChild2 != NULL_NODE_INDEX);
				}
				else
				{// leaf node must have no childs
					D_ASSERT(this->mTree.mNodes[i].mChild1 == NULL_NODE_INDEX && this->mTree.mNodes[i].mChild2 == NULL_NODE_INDEX);
				}
			}
		}


		//fourth check : check all nodes have unique child id ( all nodes have unique child id )
		//				 checked child id shouldn't be checked again
		std::unordered_set<int> checkedChildIndexs{};
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true && this->mTree.mNodes[i].mIsLeaf == false)
			{
				D_ASSERT(checkedChildIndexs.find(this->mTree.mNodes[i].mChild1) == checkedChildIndexs.end());
				D_ASSERT(checkedChildIndexs.find(this->mTree.mNodes[i].mChild2) == checkedChildIndexs.end());

				checkedChildIndexs.insert(this->mTree.mNodes[i].mChild1);
				checkedChildIndexs.insert(this->mTree.mNodes[i].mChild2);
			}
		}


		//fifth check : compare one node's parent index and parent index's child index
		for (int i = 0; i < this->mTree.mCurrentAllocatedNodeCount; i++)
		{
			if (this->mTree.mNodes[i].bmIsActive == true)
			{
				if (this->mTree.mNodes[i].mChild1 != NULL_NODE_INDEX)
				{
					D_ASSERT(this->mTree.mNodes[this->mTree.mNodes[i].mChild1].mParentIndex == i);
				}

				if (this->mTree.mNodes[i].mChild2 != NULL_NODE_INDEX)
				{
					D_ASSERT(this->mTree.mNodes[this->mTree.mNodes[i].mChild2].mParentIndex == i);
				}

				if (this->mTree.mNodes[i].mParentIndex != NULL_NODE_INDEX)
				{
					D_ASSERT(this->mTree.mNodes[this->mTree.mNodes[i].mParentIndex].mChild1 == i || this->mTree.mNodes[this->mTree.mNodes[i].mParentIndex].mChild2 == i);
				}
			}
		}

	}
#endif

	
}

template class doom::BVH<doom::physics::AABB2D>;
template class doom::BVH<doom::physics::AABB3D>;
template class doom::BVH<doom::physics::Sphere>;
