#pragma once

#include <utility>

#include <Physics/Collider/AABB.h>

namespace doom
{
	namespace physics
	{
		class BVH_TestRoom;
	}

	template <typename AABB>
	class BVH;

	template <typename AABB>
	class BVH_Tree;

	/// <summary>
	/// Node Class of BVH
	/// 
	/// Using BVH_Node_Container is recommended ( it follow RAII )
	/// </summary>
	/// <typeparam name="AABB"></typeparam>
	template <typename AABB>
	class BVH_Node
	{
		friend class BVH<AABB>;
		friend class BVH_Tree<AABB>;
		friend class doom::physics::BVH_TestRoom;

	public:

		enum class eBVH_NodeType
		{
			Stationary,
			Dynamic
		};

	private:

	
		doom::physics::Collider* mCollider{ nullptr };

		BVH<AABB>* mOwnerBVH{ nullptr };

		/// <summary>
		/// Node Bounding Box
		/// </summary>
		AABB mAABB;
		AABB mEnlargedAABB;

		/// <summary>
		/// Don't change this except in AllocateNewNode
		/// </summary>
		int mIndex{ NULL_NODE_INDEX };

		bool bmIsActive{ false };

		/// <summary>
		/// Node Index in BVH_Tree::mNodes
		/// </summary>
		int mParentIndex{ NULL_NODE_INDEX };
		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mChild1{ NULL_NODE_INDEX };

		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mChild2{ NULL_NODE_INDEX };

		/// <summary>
		/// Is Leaf? = Is World Object?
		/// </summary>
		bool mIsLeaf{ false };

		void Clear();
		/// <summary>
		/// Check Node is valid
		/// </summary>
		void ValidCheck();

		BVH_Node() = default;
		~BVH_Node() = default;
		
		BVH_Node<AABB>* UpdateNode();

		////////////////////////////////////////////////////////////////////////

	public:

		BVH_Node(const BVH_Node&) = delete;
		BVH_Node(BVH_Node&&) noexcept = delete;
		BVH_Node& operator=(const BVH_Node&) = delete;
		BVH_Node& operator=(BVH_Node&&) noexcept = delete;

		/// <summary>
		/// this function don't chagne mEnlargedAABB if newAABB is still completly enclosed by mEnlargedAABB
		/// </summary>
		/// <param name="newAABB"></param>
		BVH_Node<AABB>* UpdateAABB(const AABB& newAABB);
		/// <summary>
		/// this function don't chagne mEnlargedAABB if updated mAABB is still completly enclosed by mEnlargedAABB
		/// </summary>
		/// <param name="movedVector"></param>
		BVH_Node<AABB>* UpdateAABB(const typename AABB::component_type& movedVector);
		BVH_Node<AABB>* UpdateAABB(const typename AABB::component_type& movedVector, const typename AABB::component_type& margin);
		//Node<AABB>* UpdateAABB(const typename AABB::component_type& margin);
		void RemoveNode();

		BVH<AABB>* GetOwnerBVH();
	
	};

	

	using NodeCost = typename std::pair<int, float>;

	using BVH_Node2D = typename BVH_Node<doom::physics::AABB2D>;
	using BVH_Node3D = typename BVH_Node<doom::physics::AABB3D>;

	extern template class BVH_Node<doom::physics::AABB2D>;
	extern template class BVH_Node<doom::physics::AABB3D>;

	constexpr inline int NULL_NODE_INDEX{ -1 };
}
