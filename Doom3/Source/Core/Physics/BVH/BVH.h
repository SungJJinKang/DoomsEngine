#pragma once

#include <vector>
#include <memory>

#include "../Collider/AABB.h"
#include "Graphics/FrameBuffer/utility/PicktureInPickture.h"

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

			int mIndex{ NULL_NODE_INDEX };

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
			Node<AABB>* UpdateIfInnerAABBMoveOutsideOfEnlargedAABB();
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
			/// <summary>
			/// array
			/// Never pop inserted node
			/// Just make it dangling
			/// </summary>
			std::vector<Node<AABB>> mNodes{};


			/// <summary>
			/// Root Node Index in mNodes
			/// </summary>
			int mRootIndex{ NULL_NODE_INDEX };

		};

		using Tree2D = typename Tree<physics::AABB2D>;
		using Tree3D = typename Tree<physics::AABB3D>;


		//////////////////////////


		/// <summary>
		/// Dynamic(Incremental) BVH
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf
		/// </summary>
		/// <typeparam name="AABB"></typeparam>
		template <typename AABB>
		class BVH
		{
			using BVH_Tree = typename Tree<AABB>;
			using BVH_Node = typename Node<AABB>;

		public:
			using NodeCost = typename std::pair<int, float>;

		private:

			static inline int recentAddedLeaf{ NULL_NODE_INDEX };

			BVH_Tree mTree{};
#ifdef DEBUG_MODE
			std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
			std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
#endif
			int GetSibling(int nodeIndex);
			int PickBest(AABB& L);
			int AllocateInternalNode();
			int AllocateLeafNode(AABB& aabb, Collider* collider);
			bool RotateNode(int nodeAIndex, int nodeBIndex);
			int Balance(int index);
			void RemoveLeafNode(BVH_Node& targetLeafNode);
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

			void DebugBVHTree(BVH_Node& node, float x, float y, int depth = 0);
		public:

			constexpr BVH()
			{
			}

			static bool TreeRayCast(BVH_Tree& tree, Ray& ray);

			/// <summary>
			/// Inser New Object(Leaf)
			/// </summary>
			/// <param name="newOjectIndex"></param>
			/// <param name="newObjectBox"></param>
			BVH_Node* InsertLeaf(AABB& L, Collider* collider);

			/// <summary>
			/// file:///C:/Users/hour3/Desktop/ErinCatto_DynamicBVH_Full.pdf 96 page
			/// Will Remove updatedNode And Re-insert updateNode
			///
			/// when update leaf node, original leaf node will be destroyed(be dangled)
			/// and return new node
			/// </summary>
			/// <param name="updatedNode"></param>
			/// <returns></returns>
			BVH_Node* UpdateLeaf(BVH_Node& updatedNode);

			void InitializeDebugging();
			void SimpleDebug();
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