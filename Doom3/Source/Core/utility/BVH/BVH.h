#pragma once

#include <memory>

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Ray.h"
#include "Graphics/FrameBuffer/utility/PicktureInPickture.h"

#include "BVH_Node.h"
#include "BVH_Tree.h"

#ifdef DEBUG_MODE
#include <stack>
#endif

//BVH is used for rendering, collision detect, raycast, stero audio ......

namespace doom
{
	namespace physics
	{
		class BVH_TestRoom;
	}

	class Ray;
	template <typename AABB>
	class BVH;

	//////////////////////////

	//TODO : Two BVH ±¸Çö
	///The b3DynamicBvhBroadphase implements a broadphase using two dynamic AABB bounding volume hierarchies/trees (see b3DynamicBvh).
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
	/// <typeparam name="AABB"></typeparam>
	template <typename AABB>
	class BVH
	{
		using tree_type = typename BVH_Tree<AABB>;
		using node_type = typename BVH_Node<AABB>;

		friend class doom::physics::BVH_TestRoom;
		friend class BVH_Tree<AABB>;
		friend class BVH_Node<AABB>;
	private:

		tree_type mTree;

#ifdef DEBUG_MODE
		std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
		std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
		static inline std::stack<int> recentAddedLeaf{};
#endif
		int PickBest(const AABB& L);

		int AllocateNewNode();
		int AllocateInternalNode();
		int AllocateLeafNode(const AABB& aabb, doom::physics::Collider* collider);
		void FreeNode(int nodeIndex);

		int Balance(int lowerNodeIndex);
		void HillClimingReconstruct(int index);
		//int Balance(int index);
		void ReConstructNodeAABB(int targetNodeIndex);
		float ComputeCost();

		/// <summary>
		/// https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf see pdf 84 page
		/// </summary>
		/// <param name="newNodeAABB">Inserted AABB</param>
		/// <param name="silbingNodeIndexOfNewNode">Node what will be unioned with Inseted AABB</param>
		/// <param name="sumOfAreaSize"></param>
		/// <returns></returns>
		float InheritedCost(const AABB& L, const AABB& candidate);

		void DebugBVHTree(node_type* node, float x, float y, int depth = 0);


		void CheckActiveNode(node_type* node, std::vector<int>& activeNodeList);
		int GetSibling(int index);
		bool IsHasChild(int index);
		node_type* GetNode(int nodeIndex);
		/// <summary>
		/// longest path from node to leaf
		/// leaf node will have 0 height
		/// </summary>
		/// <param name="node"></param>
		/// <param name="index"></param>
		/// <param name="currentHeight"></param>
		/// <returns></returns>
		int GetHeight(int index, int& longestHeight = 0, int currentHeight = -1);
		int GetDepth(int index);
		int GetLeafNodeCount();
		/// <summary>
		/// Get Leaf with index
		/// </summary>
		/// <typeparam name="AABB"></typeparam>
		int GetLeaf(int index);
		bool IsAncesterOf(int ancesterIndex, int decesterIndex);

	public:

		constexpr BVH(int nodeCapacity)
			: mTree{ nodeCapacity }
		{
		}

		~BVH()
		{
		}

		bool BVHRayCast(const doom::physics::Ray& ray);

		/// <summary>
		/// Inser New Object(Leaf)
		/// </summary>
		/// <param name="newOjectIndex"></param>
		/// <param name="newObjectBox"></param>
		node_type* InsertLeaf(const AABB& L, doom::physics::Collider* collider);
		void RemoveLeafNode(node_type* targetLeafNode);
		void RemoveLeafNode(int targetLeafNodeIndex);
		
		/// <summary>
		/// Remove paased Node And Re-insert the node
		///
		/// when update leaf node, original leaf node will be destroyed(be dangled)
		/// and return new node
		/// </summary>
		/// <param name="updatedNode"></param>
		/// <param name="force"></param>
		/// <returns></returns>
		node_type* UpdateLeafNode(node_type* targetLeafNode, bool force = false);

		void InitializeDebugging();
		void TreeDebug();
		void AABBDebug(int targetNode);
		void AABBDebug();

		/// <summary>
		/// Check all active nodes can be traversed from rootNodeIndex
		/// </summary>
		void ValidCheck();
	};

	using BVH2D = typename BVH<doom::physics::AABB2D>;
	using BVH3D = typename BVH<doom::physics::AABB3D>;
	
	extern template class BVH<doom::physics::AABB2D>;
	extern template class BVH<doom::physics::AABB3D>;

}

template <>
struct std::greater<typename doom::NodeCost>
{
	constexpr bool operator()(const doom::NodeCost& lhs, const doom::NodeCost& rhs) const
	{
		return lhs.second > lhs.second;
	}
};

