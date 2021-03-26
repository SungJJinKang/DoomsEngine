#pragma once

#include <utility>

#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

#include "BVH_Core.h"
#include "BVH_Node_View.h"

#include "../TreeNode.h"

namespace doom
{
	template <typename ColliderType>
	class BVH;


	/// <summary>
	/// Node Class of BVH
	/// 
	/// Using BVH_Node_Container is recommended ( it follow RAII )
	/// </summary>
	/// <typeparam name="ColliderType"></typeparam>
	template <typename ColliderType>
	class BVH_Node : public TreeNode
	{
		friend class BVH<ColliderType>;
		friend class BVH_TestRoom;
		friend class BVH_Node_View<ColliderType>;

		using node_view_type = typename BVH_Node_View<ColliderType>;

	public:

	private:
		
		doom::physics::Collider* mCollider{ nullptr };

		BVH<ColliderType>* mOwnerBVH{ nullptr };

		/// <summary>
		/// Node Bounding Box
		/// </summary>
		ColliderType mBoundingCollider;
		ColliderType mEnlargedBoundingCollider;

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
		
		node_view_type UpdateNode();

		////////////////////////////////////////////////////////////////////////

	public:

		BVH_Node(const BVH_Node&) = delete;
		BVH_Node(BVH_Node&&) noexcept = delete;
		BVH_Node& operator=(const BVH_Node&) = delete;
		BVH_Node& operator=(BVH_Node&&) noexcept = delete;

		/// <summary>
		/// this function don't chagne mEnlargedBoundingCollider if newAABB is still completly enclosed by mEnlargedBoundingCollider
		/// </summary>
		/// <param name="collider"></param>
		node_view_type Update(const ColliderType& collider);
		/// <summary>
		/// this function don't chagne mEnlargedBoundingCollider if updated mBoundingCollider is still completly enclosed by mEnlargedBoundingCollider
		/// </summary>
		/// <param name="movedVector"></param>
		node_view_type Update(const typename ColliderType::component_type& movedVector);
		node_view_type Update(const typename ColliderType::component_type& movedVector, const typename ColliderType::component_type& margin);
		//Node<ColliderType>* Update(const typename ColliderType::component_type& margin);
		void RemoveNode();

		BVH<ColliderType>* GetOwnerBVH();
	
	};

	

	using NodeCost = typename std::pair<int, float>;

	using BVH_Node2D = typename BVH_Node<doom::physics::AABB2D>;
	using BVH_Node3D = typename BVH_Node<doom::physics::AABB3D>;
	using BVH_NodeSphere = typename BVH_Node<doom::physics::Sphere>;

	extern template class BVH_Node<doom::physics::AABB2D>;
	extern template class BVH_Node<doom::physics::AABB3D>;
	extern template class BVH_Node<doom::physics::Sphere>;

	
}
