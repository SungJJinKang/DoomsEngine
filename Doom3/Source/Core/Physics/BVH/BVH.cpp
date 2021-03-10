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
	//newNode.mCollider = collider;
	newNode.mAABB = aabb;
	newNode.mCollider = collider;
	newNode.mIsLeaf = true;
	return static_cast<int>(this->mTree.mNodes.size() - 1);
}




template <typename AABB>
int doom::physics::BVH<AABB>::AllocateInternalNode()
{
	auto& newNode = this->mTree.mNodes.emplace_back();
	newNode.mIsLeaf = false;
	return static_cast<int>(this->mTree.mNodes.size() - 1);
}




template <typename AABB>
void doom::physics::BVH<AABB>::InsertLeaf(AABB& L, Collider* collider)
{
	int newObjectLeafIndex = AllocateLeafNode(L, collider);
	if (this->mTree.mNodes.size() == 1)
	{
		this->mTree.mRootIndex = newObjectLeafIndex;
		return;
	}

	int bestSiblingIndex = PickBest(L);



	int oldParentIndex = this->mTree.mNodes[bestSiblingIndex].mParentIndex;
	int newParentIndex = AllocateInternalNode();
	this->mTree.mNodes[newParentIndex].mParentIndex = oldParentIndex;
	this->mTree.mNodes[newParentIndex].mAABB = AABB::Union(L, this->mTree.mNodes[bestSiblingIndex].mAABB);

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
		int child1 = this->mTree.mNodes[index].mChild1;
		int child2 = this->mTree.mNodes[index].mChild2;

		//AABB originalAABB = this->mTree.mNodes[index].mAABB;
		this->mTree.mNodes[index].mAABB = AABB::Union(this->mTree.mNodes[child1].mAABB, this->mTree.mNodes[child2].mAABB);

		//float increasedAreaSize{ AABB::GetArea(this->mTree.mNodes[index].mAABB) - AABB::GetArea(originalAABB) };

		index = this->mTree.mNodes[index].mParentIndex;
	}
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

template<typename AABB>
void doom::physics::BVH<AABB>::SimpleDebug()
{
	for (auto& node : this->mTree.mNodes)
	{
		node.mAABB.DrawPhysicsDebug();
	}


	if (static_cast<bool>(this->mPIPForDebug))
	{
		this->mPIPForDebug->BindFrameBuffer();

		graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		this->mPIPForDebug->ClearFrameBuffer();

		graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

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

		graphics::DebugGraphics::GetSingleton()->SetDrawInstantlyMaterial(nullptr);

		this->mPIPForDebug->RevertFrameBuffer();
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
		this->mPIPForDebug = std::make_unique<graphics::PicktureInPickture>(512, 256, math::Vector2(-1.0f, 0.4f), math::Vector2(-0.4f, 1.0f));
		graphics::Graphics_Server::GetSingleton()->AddAutoDrawedPIPs(*(this->mPIPForDebug.get()));
	}

	if (static_cast<bool>(this->mBVHDebugMaterial) == false)
	{
		this->mBVHDebugMaterial = std::make_unique<graphics::Material>( doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("Default2DColorShader.glsl"));
	}
}

template class doom::physics::BVH<doom::physics::AABB3D>;
template class doom::physics::BVH<doom::physics::AABB2D>;