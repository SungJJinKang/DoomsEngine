#pragma once

#include <type_traits>
#include "../Collider/AABB.h"
#include <stack>
#include <vector>
#include <queue>

//BVH is used for rendering, collision detect, raycast, stero audio ......

namespace doom
{
	namespace physics
	{
		class Ray;

		constexpr inline int NULL_NODE_INDEX{ -1 };

		template <typename AABB>
		struct Node
		{
			/// <summary>
			/// Node Bounding Box
			/// </summary>
			AABB mAABB;

			/// <summary>
			/// World Object Unqieu ID
			/// Will be used when mIsLeaf is true
			/// </summary>
			int mObjectIndex{ NULL_NODE_INDEX };

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
			/// </summary>
			std::vector<Node<AABB>> mNodes{};


			/// <summary>
			/// Root Node Index in mNodes
			/// </summary>
			int mRootIndex{ 0 };
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
			using NodeCost = typename std::pair<unsigned int, float>;

		protected:

			BVH_Tree mTree{};

		public:

			constexpr BVH()
			{
				AllocateInternalNode();

				AABB aabb{ 0.0f, 1.0f };
				this->InsertLeaf(0, aabb);
			}

			static bool TreeRayCast(BVH_Tree& tree, Ray& ray);

			int PickBest(AABB& aabb);

			int AllocateInternalNode();

			int AllocateLeafNode(int objectIndex, AABB& box);

			void InsertLeaf(int newOjectIndex, AABB& newObjectBox);

			float ComputeCost();

			/// <summary>
			/// see pdf 84page
			/// </summary>
			/// <param name="newNodeAABB">Inserted AABB</param>
			/// <param name="silbingNodeIndexOfNewNode">Node what will be unioned with Inseted AABB</param>
			/// <param name="sumOfAreaSize"></param>
			/// <returns></returns>
			float InheritedCost(AABB L, AABB candidate);
		};

		
		using BVH3D = typename BVH<physics::AABB3D>;
		using BVH2D = typename BVH<physics::AABB2D>;

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