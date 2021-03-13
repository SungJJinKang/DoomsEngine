#pragma once

#include <queue>
#include <memory>

#include "../Collider/AABB.h"
#include "Graphics/FrameBuffer/utility/PicktureInPickture.h"

#ifdef DEBUG_MODE
#include <stack>
#endif

//BVH is used for rendering, collision detect, raycast, stero audio ......

namespace doom
{

	namespace physics
	{
		class Ray;
		template <typename AABB>
		class BVH;

		constexpr inline int NULL_NODE_INDEX{ -1 };

		//TODO : 이거 그냥 클래스로 바꾸고 AABB랑 데이터들 private으로 보호하자, 그리고 BVH를 friendclass로 두자
		template <typename AABB>
		struct Node
		{
			BVH<AABB>* mOwnerBVH{ nullptr };

			/// <summary>
			/// Node Bounding Box
			/// </summary>
			AABB mAABB;
			AABB mEnlargedAABB;

			Collider* mCollider{ nullptr };

			/// <summary>
			/// Don't change this except in AllocateNewNode
			/// </summary>
			int mIndex{ NULL_NODE_INDEX };

			bool bmIsActive{ false };
			
		

			/// <summary>
			/// Node Index in Tree::mNodes
			/// </summary>
			int mParentIndex{ NULL_NODE_INDEX };
			/// <summary>
			/// Node index in Tree::mNodes
			/// </summary>
			int mChild1{ NULL_NODE_INDEX };

			/// <summary>
			/// Node index in Tree::mNodes
			/// </summary>
			int mChild2{ NULL_NODE_INDEX };

			/// <summary>
			/// Is Leaf? = Is World Object?
			/// </summary>
			bool mIsLeaf{ false };

			/// <summary>
			/// this function don't chagne mEnlargedAABB if newAABB is still completly enclosed by mEnlargedAABB
			/// </summary>
			/// <param name="newAABB"></param>
			Node<AABB>* UpdateAABB(const AABB& newAABB);
			/// <summary>
			/// this function don't chagne mEnlargedAABB if updated mAABB is still completly enclosed by mEnlargedAABB
			/// </summary>
			/// <param name="movedVector"></param>
			Node<AABB>* UpdateAABB(const typename AABB::component_type& movedVector);
			Node<AABB>* UpdateAABB(const typename AABB::component_type& movedVector, const typename AABB::component_type& margin);
			//Node<AABB>* UpdateAABB(const typename AABB::component_type& margin);
			Node<AABB>* UpdateIfInnerAABBMoveOutsideOfEnlargedAABB();

			void Clear();
			/// <summary>
			/// Check Node is valid
			/// </summary>
			void ValidCheck();
		};

		using Node2D = typename Node<physics::AABB2D>;
		using Node3D = typename Node<physics::AABB3D>;
		

		//////////////////////////


		/// <summary>
		/// 
		/// </summary>
		template <typename AABB>
		struct Tree
		{

			int mRootNodeIndex{ NULL_NODE_INDEX };

			/// <summary>
			/// array
			/// Never pop inserted node
			/// Just make it dangling
			/// </summary>
			Node<AABB>* mNodes { nullptr };
			const int mNodeCapacity;

			/// <summary>
			/// Ever used Node Count
			/// this value contain freed node count
			/// </summary>
			int mCurrentAllocatedNodeCount{ 0 };
			/// <summary>
			/// Current used node count
			/// this value doesn't contain freed node count
			/// </summary>
			int mCurrentActiveNodeCount{ 0 };
			/// <summary>
			/// if you want parallel access, Use concurrentQueue
			/// </summary>
			std::queue<int> freedNodeIndexList{};

			Tree(int nodeCapacity)
				: mNodeCapacity{ nodeCapacity }
			{
				this->mNodes = new Node<AABB>[mNodeCapacity]();
			}

		};

		/*
		template <int NodeCount>
		using Tree2D = typename Tree<physics::AABB2D, NodeCount>;

		template <int NodeCount>
		using Tree3D = typename Tree<physics::AABB3D, NodeCount>;
		*/

		//////////////////////////

		//TODO : Two BVH 구현
		///The b3DynamicBvhBroadphase implements a broadphase using two dynamic AABB bounding volume hierarchies/trees (see b3DynamicBvh).
		///One tree is used for static/non-moving objects, and another tree is used for dynamic objects. Objects can move from one tree to the other.
		///This is a very fast broadphase, especially for very dynamic worlds where many objects are moving. Its insert/add and remove of objects is generally faster than the sweep and prune broadphases b3AxisSweep3 and b332BitAxisSweep3.
		//struct b3DynamicBvhBroadphase
		//https://github.com/bulletphysics/bullet3/blob/master/src/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.h

		//TODO : make Parallel BVH construction 
		//https://meistdan.github.io/publications/phr/paper.pdf

		//https://graphics.cg.uni-saarland.de/courses/cg1-2019/slides/Building_Good_BVHs.pdf

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
			friend class BVH_TestRoom;

			using BVH_Tree = typename Tree<AABB>;
			using BVH_Node = typename Node<AABB>;

		public:
			using NodeCost = typename std::pair<int, float>;

		private:

			
			BVH_Tree mTree;

#ifdef DEBUG_MODE
			std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
			std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
#endif
			int PickBest(AABB& L);

			int AllocateNewNode();
			int AllocateInternalNode();
			int AllocateLeafNode(AABB& aabb, Collider* collider);
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

			void DebugBVHTree(BVH_Node* node, float x, float y, int depth = 0);

		
			void CheckActiveNode(BVH_Node* node, std::vector<int>& activeNodeList);

			int GetSibling(int index);
			bool IsHasChild(int index);
		public:
#ifdef DEBUG_MODE
			static inline std::stack<int> recentAddedLeaf{};
#endif
			constexpr BVH(int nodeCapacity)
				: mTree{ nodeCapacity }
			{

			}

			static bool TreeRayCast(BVH_Tree& tree, Ray& ray);

			/// <summary>
			/// Inser New Object(Leaf)
			/// </summary>
			/// <param name="newOjectIndex"></param>
			/// <param name="newObjectBox"></param>
			BVH_Node* InsertLeaf(AABB& L, Collider* collider);
			void RemoveLeafNode(BVH_Node* targetLeafNode);
			void RemoveLeafNode(int targetLeafNodeIndex);
			/// <summary>
			/// file:///C:/Users/hour3/Desktop/ErinCatto_DynamicBVH_Full.pdf 96 page
			/// Will Remove updatedNode And Re-insert updateNode
			///
			/// when update leaf node, original leaf node will be destroyed(be dangled)
			/// and return new node
			/// </summary>
			/// <param name="updatedNode"></param>
			/// <returns></returns>
			BVH_Node* UpdateLeaf(BVH_Node* updatedNode);

			void InitializeDebugging();
			void TreeDebug();
			void AABBDebug(int targetNode);
			void AABBDebug();


			BVH_Node* GetNode(int nodeIndex);


			/// <summary>
			/// Check all active nodes can be traversed from rootNodeIndex
			/// </summary>
			void ValidCheck();

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
		};

		
		using BVH3D = typename BVH<physics::AABB3D>;
		using BVH2D = typename BVH<physics::AABB2D>;
		
		extern template class BVH<physics::AABB3D>;
		extern template class BVH<physics::AABB2D>;
		

	

}
}

template <>
struct std::greater<typename doom::physics::BVH<doom::physics::AABB3D>::NodeCost>
{
	constexpr bool operator()(const doom::physics::BVH<doom::physics::AABB3D>::NodeCost& lhs, const doom::physics::BVH<doom::physics::AABB3D>::NodeCost& rhs) const
	{
		return lhs.second > lhs.second;
	}
};