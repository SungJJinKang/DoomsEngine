#include "BVH.h"

#include <stack>
#include <queue>
#include <type_traits>
#include <utility>

#include "../Collider/Collider.h"
#include "../Collider/Ray.h"
#include "../Collider/PhysicsGeneric.h"
#include "../Collider/ColliderSolution.h"

#include "../../Graphics/DebugGraphics.h"

#include "Graphics/Graphics_Server.h"
#include "Graphics/GraphicsAPI.h"
#include "Game/AssetManager/AssetManager.h"
#include "Graphics/Material.h"

template<typename AABB>
doom::physics::Node<AABB>* doom::physics::Node<AABB>::UpdateAABB(const AABB& newAABB)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mAABB = newAABB;
	return this->UpdateIfInnerAABBMoveOutsideOfEnlargedAABB();
}

template<typename AABB>
doom::physics::Node<AABB>* doom::physics::Node<AABB>::UpdateAABB(const typename AABB::component_type& movedVector)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mAABB.MoveAABB(movedVector);
	return this->UpdateIfInnerAABBMoveOutsideOfEnlargedAABB();
}

template<typename AABB>
doom::physics::Node<AABB>* doom::physics::Node<AABB>::UpdateIfInnerAABBMoveOutsideOfEnlargedAABB()
{
	D_ASSERT(this->mIsLeaf == true); // Only Leaf Nodes can be updated by UpdateLeaf Function
	if (CheckIsAABBCompletlyEnclosed(this->mAABB, this->mEnlargedAABB) == false)
	{
		return this->mOwnerBVH->UpdateLeaf(*this);
	}
	else
	{
		return this;
	}
}

template <typename AABB>
bool doom::physics::BVH<AABB>::TreeRayCast(BVH<AABB>::BVH_Tree& tree, Ray & ray)

{
	std::stack<int> stack{};
	stack.push(tree.mRootIndex);
	while (stack.empty() == false)
	{
		int index = stack.top();
		stack.pop();

		if constexpr (std::is_same_v<doom::physics::AABB2D, AABB> == true)
		{
			if (doom::physics::IsOverlapRayAndAABB2D(ray, tree.mNodes[index].mAABB) == false)
			{// if don't hit with bounding box
				continue;
			}
		}
		else if (std::is_same_v<doom::physics::AABB3D, AABB> == true)
		{
			if (doom::physics::IsOverlapRayAndAABB3D(ray, tree.mNodes[index].mAABB) == false)
			{// if don't hit with bounding box
				continue;
			}
		}
		else
		{
			NEVER_HAPPEN;
		}


		if (tree.mNodes[index].mIsLeaf)
		{//if node is world object

			if (ColliderSolution::CheckIsOverlap(tree.mNodes[index].mCollider, static_cast<Collider*>(&ray)) == true)
			{// check collision with ray and world object collider
				return true;
			}
		}
		else
		{
			stack.push(tree.mNodes[index].mChild1);
			stack.push(tree.mNodes[index].mChild2);
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
/// <typeparam name="AABB"></typeparam>
/// <param name="siblindInex"></param>
/// <param name="computedAreaSize"></param>
/// <returns></returns>
template <typename AABB>
int doom::physics::BVH<AABB>::PickBest(AABB& L)
{
	//https://github.com/selimanac/DAABBCC/blob/v2.0/daabbcc/src/DynamicTree/b2DynamicTree.cpp


	using node_priority_queue_type_t = typename std::priority_queue<NodeCost, std::vector<NodeCost>, std::greater<NodeCost>>;
	node_priority_queue_type_t queue{};
	queue.push(std::make_pair(this->mTree.mRootIndex, InheritedCost(L, this->mTree.mNodes[this->mTree.mRootIndex].mAABB)));

	float toInsertSurfaceArea = AABB::GetArea(L);
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

		AABB& search_aabb = this->mTree.mNodes[searchIndex].mAABB;

		//Why Get UnionArea L with Ancestors  ??
		//If you want ancester's area of newly inserted node, you just be needed to compute unioned area with them
		float cost = AABB::GetUnionArea(L, search_aabb) + searchInheritedCost;
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

template <typename AABB>
int doom::physics::BVH<AABB>::AllocateLeafNode(AABB& aabb, Collider* collider)
{
	auto& newNode = this->mTree.mNodes.emplace_back();

	newNode.mIndex = static_cast<int>(this->mTree.mNodes.size() - 1);
	newNode.mOwnerBVH = this;

	//newNode.mCollider = collider;
	newNode.mAABB = aabb;
	newNode.mEnlargedAABB = AABB::EnlargeAABB(newNode.mAABB);

	newNode.mCollider = collider;
	newNode.mIsLeaf = true;

	recentAddedLeaf = newNode.mIndex;

	return newNode.mIndex;
}




template <typename AABB>
int doom::physics::BVH<AABB>::AllocateInternalNode()
{
	auto& newNode = this->mTree.mNodes.emplace_back();
	newNode.mOwnerBVH = this;

	newNode.mIsLeaf = false;
	newNode.mIndex = static_cast<int>(this->mTree.mNodes.size() - 1);

	return newNode.mIndex;
}




template <typename AABB>
typename doom::physics::BVH<AABB>::BVH_Node* doom::physics::BVH<AABB>::InsertLeaf(AABB& L, Collider* collider)
{
	int newObjectLeafIndex = AllocateLeafNode(L, collider);
	if (this->mTree.mNodes.size() == 1)
	{// if allocate first node, this->mTree.mNodes.size() will be 1
		this->mTree.mRootIndex = newObjectLeafIndex;
	}
	else
	{
		int bestSiblingIndex = PickBest(L);



		int oldParentIndex = this->mTree.mNodes[bestSiblingIndex].mParentIndex;
		int newParentIndex = AllocateInternalNode();
		this->mTree.mNodes[newParentIndex].mParentIndex = oldParentIndex;
		this->mTree.mNodes[newParentIndex].mAABB = AABB::Union(L, this->mTree.mNodes[bestSiblingIndex].mAABB);
		this->mTree.mNodes[newParentIndex].mEnlargedAABB = AABB::EnlargeAABB(this->mTree.mNodes[newParentIndex].mAABB);

		if (oldParentIndex != NULL_NODE_INDEX)
		{
			if (this->mTree.mNodes[oldParentIndex].mChild1 == bestSiblingIndex)
			{
				this->mTree.mNodes[oldParentIndex].mChild1 = newParentIndex;
			}
			else
			{
				this->mTree.mNodes[oldParentIndex].mChild2 = newParentIndex;
			}

			this->mTree.mNodes[newParentIndex].mChild1 = bestSiblingIndex;
			this->mTree.mNodes[newParentIndex].mChild2 = newObjectLeafIndex;
			this->mTree.mNodes[bestSiblingIndex].mParentIndex = newParentIndex;
			this->mTree.mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
		}
		else
		{
			this->mTree.mNodes[newParentIndex].mChild1 = bestSiblingIndex;
			this->mTree.mNodes[newParentIndex].mChild2 = newObjectLeafIndex;
			this->mTree.mNodes[bestSiblingIndex].mParentIndex = newParentIndex;
			this->mTree.mNodes[newObjectLeafIndex].mParentIndex = newParentIndex;
			this->mTree.mRootIndex = newParentIndex;

		}

		//walk back, recalculate new leaf nodes's ancesters AABBs
		int index = this->mTree.mNodes[newObjectLeafIndex].mParentIndex;
		while (index != NULL_NODE_INDEX)
		{
			//index = Balance(index);

			int child1 = this->mTree.mNodes[index].mChild1;
			int child2 = this->mTree.mNodes[index].mChild2;

			D_ASSERT(child1 != NULL_NODE_INDEX && child2 != NULL_NODE_INDEX);

			//AABB originalAABB = this->mTree.mNodes[index].mAABB;
			this->mTree.mNodes[index].mAABB = AABB::Union(this->mTree.mNodes[child1].mAABB, this->mTree.mNodes[child2].mAABB);
			this->mTree.mNodes[index].mEnlargedAABB = AABB::EnlargeAABB(this->mTree.mNodes[index].mAABB);
			//float increasedAreaSize{ AABB::GetArea(this->mTree.mNodes[index].mAABB) - AABB::GetArea(originalAABB) };

			index = this->mTree.mNodes[index].mParentIndex;
		}
	}

	return &(this->mTree.mNodes[newObjectLeafIndex]);
}

template <typename AABB>
typename doom::physics::BVH<AABB>::BVH_Node* doom::physics::BVH<AABB>::UpdateLeaf(BVH_Node& updatedNode)
{
	//we will remove node and re-insert node
	this->RemoveLeafNode(updatedNode);
	return this->InsertLeaf(updatedNode.mAABB, updatedNode.mCollider);
}

/// <summary>
/// When union with new aabb,
/// How much is AABB larger than before
/// 
/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf 77p
/// SA mean area of aabb
/// 세모SA(Node) = SA(Node U L) - SA(Node)  -----> 한 AABB에서 새 AABB를 합치면 얼만큼 Area가 추가되는지
/// </summary>
/// <typeparam name="AABB"></typeparam>
/// <param name="L"></param>
/// <param name="candidate"></param>
/// <returns></returns>
template <typename AABB>
float doom::physics::BVH<AABB>::InheritedCost(const AABB& L, const AABB& candidate)
{
	return AABB::GetUnionArea(L, candidate) - AABB::GetArea(candidate);
}

template <typename AABB>
int doom::physics::BVH<AABB>::GetSibling(int nodeIndex)
{
	int nodeParentIndex = this->mTree.mNodes[nodeIndex].mParentIndex;
	return (nodeIndex == this->mTree.mNodes[nodeParentIndex].mChild1) ? this->mTree.mNodes[nodeParentIndex].mChild2 : this->mTree.mNodes[nodeParentIndex].mChild1;
}

/// <summary>
/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf 117 page
/// </summary>
/// <typeparam name="AABB"></typeparam>
/// <param name="nodeAIndex"></param>
/// <param name="nodeBIndex"></param>
template <typename AABB>
bool doom::physics::BVH<AABB>::RotateNode(int nodeAIndex, int nodeBIndex)
{
	D_ASSERT(nodeAIndex != NULL_NODE_INDEX);
	D_ASSERT(nodeBIndex != NULL_NODE_INDEX);

	int nodeAParentIndex = this->mTree.mNodes[nodeAIndex].mParentIndex;
	int nodeBParentIndex = this->mTree.mNodes[nodeBIndex].mParentIndex;

	if (nodeAParentIndex == NULL_NODE_INDEX || nodeBParentIndex == NULL_NODE_INDEX)
	{
		return false;
	}

	int nodeASiblingIndex = (nodeAIndex == this->mTree.mNodes[nodeAParentIndex].mChild1) ? this->mTree.mNodes[nodeAParentIndex].mChild2 : this->mTree.mNodes[nodeAParentIndex].mChild1;
	int nodeBSiblingIndex = (nodeBIndex == this->mTree.mNodes[nodeBParentIndex].mChild1) ? this->mTree.mNodes[nodeBParentIndex].mChild2 : this->mTree.mNodes[nodeBParentIndex].mChild1;
	
	int rotatedNode{};
	int siblingChildOfRotatedNode{};
	if (nodeAParentIndex == nodeBSiblingIndex)
	{
		rotatedNode = nodeBIndex;
		siblingChildOfRotatedNode = nodeAIndex;
	}
	else if (nodeBParentIndex == nodeASiblingIndex)
	{
		rotatedNode = nodeAIndex;
		siblingChildOfRotatedNode = nodeBIndex;
	}
	else
	{
		return false;
	}

	int parentOfRotatedNode = this->mTree.mNodes[rotatedNode].mParentIndex;
	int parentOfsiblingChildOfRotatedNode = this->mTree.mNodes[siblingChildOfRotatedNode].mParentIndex;

	if (this->mTree.mNodes[parentOfRotatedNode].mChild1 == rotatedNode)
	{
		if (this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild1 == siblingChildOfRotatedNode)
		{
			this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild1 = rotatedNode;
			this->mTree.mNodes[parentOfRotatedNode].mChild1 = siblingChildOfRotatedNode;
		}
		else if (this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild2 == siblingChildOfRotatedNode)
		{
			this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild2 = rotatedNode;
			this->mTree.mNodes[parentOfRotatedNode].mChild1 = siblingChildOfRotatedNode;
		}

		ReConstructNodeAABB(this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mIndex);
		return true;
	}
	else if (this->mTree.mNodes[parentOfRotatedNode].mChild2 == rotatedNode)
	{
		if (this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild1 == siblingChildOfRotatedNode)
		{
			this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild1 = rotatedNode;
			this->mTree.mNodes[parentOfRotatedNode].mChild2 = siblingChildOfRotatedNode;
		}
		else if (this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild2 == siblingChildOfRotatedNode)
		{
			this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mChild2 = rotatedNode;
			this->mTree.mNodes[parentOfRotatedNode].mChild2 = siblingChildOfRotatedNode;
		}

		ReConstructNodeAABB(this->mTree.mNodes[parentOfsiblingChildOfRotatedNode].mIndex);
		return true;
	}
	else
	{
		NEVER_HAPPEN;
	}

}

/// <summary>
/// https://www.computer.org/csdl/pds/api/csdl/proceedings/download-article/12OmNwEJ11o/pdf
/// </summary>
/// <typeparam name="AABB"></typeparam>
/// <param name="index"></param>
/// <returns></returns>
template <typename AABB>
int doom::physics::BVH<AABB>::Balance(int index)
{
	return 0;
}

template<typename AABB>
void doom::physics::BVH<AABB>::RemoveLeafNode(doom::physics::BVH<AABB>::BVH_Node& targetLeafNode)
{
	int targetLeafNodeIndex = targetLeafNode.mIndex;

	D_ASSERT(this->mTree.mNodes[targetLeafNodeIndex].mIsLeaf == true);

	int parentIndex = this->mTree.mNodes[targetLeafNodeIndex].mParentIndex;
	int grandParentIndex = this->mTree.mNodes[parentIndex].mParentIndex;
	int siblingIndex;
	if (this->mTree.mNodes[parentIndex].mChild1 == targetLeafNodeIndex)
	{
		siblingIndex = this->mTree.mNodes[parentIndex].mChild2;
	}
	else if(this->mTree.mNodes[parentIndex].mChild2 == targetLeafNodeIndex)
	{
		siblingIndex = this->mTree.mNodes[parentIndex].mChild1;
	}
	else
	{
		NEVER_HAPPEN;
	}

	if (grandParentIndex == NULL_NODE_INDEX)
	{
		this->mTree.mRootIndex = siblingIndex;
		this->mTree.mNodes[siblingIndex].mParentIndex = NULL_NODE_INDEX;
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

		this->mTree.mNodes[siblingIndex].mParentIndex = grandParentIndex;

		int index = grandParentIndex;
		while (index != NULL_NODE_INDEX)
		{
			//index = Balance(index);

			int child1 = this->mTree.mNodes[index].mChild1;
			int child2 = this->mTree.mNodes[index].mChild2;

			this->mTree.mNodes[index].mAABB = AABB::Union(this->mTree.mNodes[child1].mAABB, this->mTree.mNodes[child2].mAABB);
			this->mTree.mNodes[index].mEnlargedAABB = AABB::EnlargeAABB(this->mTree.mNodes[index].mAABB);

			index = this->mTree.mNodes[index].mParentIndex;
		}
	}
}

template<typename AABB>
void doom::physics::BVH<AABB>::ReConstructNodeAABB(int targetNodeIndex)
{
	D_ASSERT(this->mTree.mNodes.size() > targetNodeIndex);

	bool isReset{ false };
	if (this->mTree.mNodes[targetNodeIndex].mChild1 != NULL_NODE_INDEX && this->mTree.mNodes[targetNodeIndex].mChild2 != NULL_NODE_INDEX)
	{
		this->mTree.mNodes[targetNodeIndex].mAABB = AABB::Union(this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mChild1].mAABB, this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mChild2].mAABB);
		isReset = true;
	}
	else if (this->mTree.mNodes[targetNodeIndex].mChild1 != NULL_NODE_INDEX)
	{
		this->mTree.mNodes[targetNodeIndex].mAABB = this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mChild1].mAABB;
		isReset = true;
	}
	else if (this->mTree.mNodes[targetNodeIndex].mChild2 != NULL_NODE_INDEX)
	{
		this->mTree.mNodes[targetNodeIndex].mAABB = this->mTree.mNodes[this->mTree.mNodes[targetNodeIndex].mChild2].mAABB;
		isReset = true;
	}

	if (isReset == true)
	{
		this->mTree.mNodes[targetNodeIndex].mEnlargedAABB = AABB::EnlargeAABB(this->mTree.mNodes[targetNodeIndex].mAABB);
	}
}

#define DebugBVHTreeOffsetX 0.1f
#define DebugBVHTreeOffsetY 0.1f

float additionalWeight(float x, float l)
{
	return x + math::lerp(0, x > 0 ? 1 : -1, math::abs(l));
}

template <typename AABB>
void doom::physics::BVH<AABB>::DebugBVHTree(BVH_Node& node, float x, float y, int depth)
{
	float offsetX = 1.0f / (math::pow(2, depth + 1));
	if (node.mChild1 != NULL_NODE_INDEX)
	{
		graphics::DebugGraphics::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x - offsetX, y - DebugBVHTreeOffsetY, 0 }, this->mTree.mNodes[node.mChild1].mIsLeaf == false ? eColor::Black : (doom::physics::BVH<AABB>::recentAddedLeaf == node.mChild1 ? eColor::Red : eColor::Blue), false, true);
		DebugBVHTree(this->mTree.mNodes[node.mChild1], x - offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
	if (node.mChild2 != NULL_NODE_INDEX)
	{
		graphics::DebugGraphics::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x + offsetX, y - DebugBVHTreeOffsetY, 0 }, this->mTree.mNodes[node.mChild2].mIsLeaf == false ? eColor::Black : (doom::physics::BVH<AABB>::recentAddedLeaf == node.mChild2 ? eColor::Red : eColor::Blue), false, true);
		DebugBVHTree(this->mTree.mNodes[node.mChild2], x + offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
}

template<typename AABB>
void doom::physics::BVH<AABB>::SimpleDebug()
{
	if (this->mTree.mRootIndex != NULL_NODE_INDEX)
	{
		for (auto& node : this->mTree.mNodes)
		{
			node.mAABB.DrawPhysicsDebug(); // TODO : Draw recursively, don't draw all nodes
		}



		if (static_cast<bool>(this->mPIPForDebug))
		{
			this->mPIPForDebug->BindFrameBuffer();

			graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			this->mPIPForDebug->ClearFrameBuffer();

			graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

			DebugBVHTree(this->mTree.mNodes[this->mTree.mRootIndex], 0, 1, 0);

			/*
			if constexpr (std::is_same_v<doom::physics::AABB2D, AABB> == true)
			{
				for (auto& node : this->mTree.mNodes)
				{
					node.mAABB.DrawPhysicsDebugColor(eColor::Red, true);
				}

			}
			else if (std::is_same_v<doom::physics::AABB3D, AABB> == true)
			{
				for (auto& node : this->mTree.mNodes)
				{
					node.mAABB.Render2DTopView(eColor::Red, true);
				}
			}
			*/

			graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(nullptr);

			this->mPIPForDebug->RevertFrameBuffer();
		}
	}
}


/// <summary>
/// We will get sum of Internal Nodes's area
/// 
/// Less sum of Internal Nodes's area -> More fast Ray cast
/// </summary>
/// <typeparam name="AABB"></typeparam>
/// <returns></returns>
template <typename AABB>
float doom::physics::BVH<AABB>::ComputeCost()
{
	float cost{ 0.0f };
	for (auto& node : this->mTree.mNodes)
	{
		if (node.mIsLeaf == false)
		{
			cost += AABB::GetArea(node.mAABB);
		}
	}
	return cost;
}


template <typename AABB>
void doom::physics::BVH<AABB>::InitializeDebugging()
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

template class doom::physics::BVH<doom::physics::AABB3D>;
template class doom::physics::BVH<doom::physics::AABB2D>;