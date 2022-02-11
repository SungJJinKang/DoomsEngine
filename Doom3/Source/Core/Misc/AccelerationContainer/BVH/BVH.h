#pragma once

#include <queue>
#include <vector>

#include <Core.h>

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include "BVH_Core.h"
#include "BVH_Node.h"
#include "BVH_Node_View.h"



//BVH is used for rendering, collision detect, raycast, stero audio ......

namespace dooms
{
	
	class Ray;
	template <typename ColliderType>
	class BVH;

	//////////////////////////

	//TODO : Two BVH ����
	///The b3DynamicBvhBroadphase implements a broadphase using two dynamic ColliderType bounding volume hierarchies/trees (see b3DynamicBvh).
	///One tree is used for static/non-moving objects, and another tree is used for dynamic objects. Objects can move from one tree to the other.
	///This is a very fast broadphase, especially for very dynamic worlds where many objects are moving. Its insert/add and remove of objects is generally faster than the sweep and prune broadphases b3AxisSweep3 and b332BitAxisSweep3.
	//struct b3DynamicBvhBroadphase
	//https://github.com/bulletphysics/bullet3/blob/master/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.h

	//TODO : make Parallel BVH construction 
	//https://meistdan.github.io/publications/phr/paper.pdf

	//https://graphics.cg.uni-saarland.de/courses/cg1-2019/slides/Building_Good_BVHs.pdf
	//http://www.cs.uu.nl/docs/vakken/magr/2016-2017/slides/lecture%2003%20-%20the%20perfect%20BVH.pdf

	/// <summary>
	/// Dynamic(Incremental) BVH
	/// reference : 
	/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf
	/// https://www.researchgate.net/publication/270704721_Incremental_BVH_construction_for_ray_tracing
	/// https://github.com/bulletphysics/bullet3/blob/master/src/BulletCollision/BroadphaseCollision/btDbvt.cpp
	/// </summary>
	/// <typeparam name="ColliderType"></typeparam>
	template <typename ColliderType>
	class D_CLASS BVH : public DObject
	{

	public:

		using node_type = typename BVH_Node<ColliderType>;
		using node_view_type = typename BVH_Node_View<ColliderType>;

	private:

		/// <summary>
		/// array
		/// Never pop inserted node
		/// Just make it dangling
		/// </summary>
		std::vector<BVH_Node<ColliderType>> mNodes;

		INT32 mRootNodeIndex{ NULL_NODE_INDEX };

		/// <summary>
		/// Ever used Node Count
		/// this value contain freed node count
		/// </summary>
		INT32 mCurrentAllocatedNodeCount{ 0 };
		/// <summary>
		/// Current used node count
		/// this value doesn't contain freed node count
		/// </summary>
		INT32 mCurrentActiveNodeCount{ 0 };
		/// <summary>
		/// if you want parallel access, Use concurrentQueue
		/// </summary>
		std::queue<INT32> mFreedNodeIndexList{};

		INT32 PickBest(const ColliderType& L);

		INT32 AllocateNewNode();
		INT32 AllocateInternalNode();
		INT32 AllocateLeafNode(const ColliderType& boundingCollider, dooms::physics::Collider* collider);
		void FreeNode(INT32 nodeIndex);

		INT32 Balance(INT32 lowerNodeIndex);
		void HillClimingReconstruct(INT32 index);
		//INT32 Balance(INT32 index);
		void ReConstructNodeAABB(INT32 targetNodeIndex);
		FLOAT32 ComputeCost();

		/// <summary>
		/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf see pdf 84 page
		/// </summary>
		/// <param name="newNodeAABB">Inserted ColliderType</param>
		/// <param name="silbingNodeIndexOfNewNode">Node what will be unioned with Inseted ColliderType</param>
		/// <param name="sumOfAreaSize"></param>
		/// <returns></returns>
		FLOAT32 InheritedCost(const ColliderType& L, const ColliderType& candidate);

	public:

		

		BVH(const size_t initializedCapacity);
		~BVH();

		inline size_t GetNodeCapacity() const
		{
			return mNodes.capacity();
		}

		/// <summary>
		/// Inser New Object(Leaf)
		/// </summary>
		/// <param name="newOjectIndex"></param>
		/// <param name="newObjectBox"></param>
		node_view_type InsertLeaf(const ColliderType& L, dooms::physics::Collider* collider);
		void RemoveLeafNode(node_type* targetLeafNode);
		void RemoveLeafNode(INT32 targetLeafNodeIndex);
		
		/// <summary>
		/// Remove paased Node And Re-insert the node
		///
		/// when update leaf node, original leaf node will be destroyed(be dangled)
		/// and return new node
		/// </summary>
		/// <param name="updatedNode"></param>
		/// <param name="force"></param>
		/// <returns></returns>
		node_view_type UpdateLeafNode(const INT32 targetLeafNodeIndex, const bool force = false);

		template <typename UnaryFunction>
		void Traverse(UnaryFunction f)
		{

		}

		typename node_type* GetRootNode();
		const typename node_type* GetRootNode() const;
		INT32 GetRootNodeIndex() const;

		INT32 GetSiblingNodeIndex(const INT32 index) const;
		typename node_type* GetSiblingNode(const INT32 index);
		const typename node_type* GetSiblingNode(const INT32 index) const;

		bool IsHasChild(const INT32 index) const;
		node_type* GetNode(const INT32 nodeIndex);
		const node_type* GetNode(const INT32 nodeIndex) const;
		bool GetIsNodeValid(const INT32 nodeIndex) const;
		bool GetIsNodeValid(const node_type* const node) const;

		/// <summary>
		/// longest path from node to leaf
		/// leaf node will have 0 height
		/// </summary>
		/// <param name="node"></param>
		/// <param name="index"></param>
		/// <param name="currentHeight"></param>
		/// <returns></returns>
		INT32 GetHeight(const INT32 index, INT32& longestHeight, INT32 currentHeight);
		INT32 GetDepth(const INT32 index);
		INT32 GetLeafNodeCount();
		/// <summary>
		/// Get Leaf with index
		/// </summary>
		/// <typeparam name="ColliderType"></typeparam>
		INT32 GetLeaf(const INT32 index);
		bool IsAncesterOf(const INT32 ancesterIndex, const INT32 decesterIndex);
		

		node_view_type MakeBVH_Node_View(INT32 index)
		{
			D_ASSERT(index < mCurrentAllocatedNodeCount);
			return node_view_type(this, index);
		}
	};

	using BVHAABB2D = typename BVH<dooms::physics::AABB2D>;
	using BVHAABB3D = typename BVH<dooms::physics::AABB3D>;
	using BVHSphere = typename BVH<dooms::physics::Sphere>;
	
	extern template class BVH<dooms::physics::AABB2D>;
	extern template class BVH<dooms::physics::AABB3D>;
	extern template class BVH<dooms::physics::Sphere>;


	using NodeCost = typename std::pair<INT32, FLOAT32>;
}


template <>
struct std::greater<typename dooms::NodeCost>
{
	bool operator()(const dooms::NodeCost& lhs, const dooms::NodeCost& rhs) const
	{
		return lhs.second > lhs.second;
	}
};

