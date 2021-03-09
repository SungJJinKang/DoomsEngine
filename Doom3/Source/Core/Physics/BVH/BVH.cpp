#include "BVH.h"


#include "../Collider/Collider.h"
#include "../Collider/Ray.h"
#include "../Collider/PhysicsGeneric.h"
#include "../Collider/ColliderSolution.h"


template <typename AABB>
bool doom::physics::BVH<AABB>::TreeRayCast(BVH<AABB>::BVH_Tree& tree, Ray & ray)

{
	std::stack<int> stack{};
	stack.push(tree.mRootIndex);
	while (stack.empty() == false)
	{
		int index = stack.top();
		stack.pop();

		
		if (RaycastRayAndAABB3D(ray, tree.mNodes[index].mAABB) == false)
		{// if don't hit with bounding box
			continue;
		}

		if (tree.mNodes[index].mIsLeaf)
		{//if node is world object
			int objectIndex = tree.mNodes[index].mObjectIndex;

			Collider* objectCollider{};
			if (ColliderSolution::CheckIsOverlap(objectCollider, static_cast<Collider*>(&ray)) == true)
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
	float bestCost = FLT_MAX;
	int bestIndex = NULL_NODE_INDEX;
	int searchIndex;
	float searchInheritedCost;

	while (queue.size() > 0)
	{
		NodeCost node = queue.top();
		queue.pop();

		searchIndex = node.first;
		searchInheritedCost = node.second;

		AABB search_aabb = this->mTree.mNodes[searchIndex].mAABB;
		float cost = AABB::GetUnionArea(L, search_aabb) + searchInheritedCost;
		if (cost < bestCost) {
			bestCost = cost;
			bestIndex = searchIndex;
		}

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
int doom::physics::BVH<AABB>::AllocateLeafNode(int objectIndex, AABB& box)
{
	auto& newNode = this->mTree.mNodes.emplace_back();
	newNode.mObjectIndex = objectIndex;
	newNode.mAABB = box;
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
void doom::physics::BVH<AABB>::InsertLeaf(int newOjectIndex, AABB& newObjectBox)
{
	int newObjectLeafIndex = AllocateLeafNode(newOjectIndex, newObjectBox);
	if (this->mTree.mNodes.size() == 1)
	{
		this->mTree.mRootIndex = newObjectLeafIndex;
		return;
	}

	int bestSiblingIndex = PickBest(newObjectBox);



	int oldParentIndex = this->mTree.mNodes[bestSiblingIndex].mParentIndex;
	int newParentIndex = AllocateInternalNode();
	this->mTree.mNodes[newParentIndex].mParentIndex = oldParentIndex;
	this->mTree.mNodes[newParentIndex].mAABB = AABB::Union(newObjectBox, this->mTree.mNodes[bestSiblingIndex].mAABB);

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
	//see pdf 84page
template <typename AABB>
float doom::physics::BVH<AABB>::InheritedCost(AABB L, AABB candidate)
{
	return AABB::GetUnionArea(L, candidate) - AABB::GetArea(candidate);
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

	doom::physics::BVH<doom::physics::AABB3D> bvh{};
