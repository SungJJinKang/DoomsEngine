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

		using node_view_type = typename BVH_Node_View<ColliderType>;

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
		void ValidCheck() const;
	
	


	public:

		BVH_Node() = default;
		~BVH_Node() = default;

		BVH_Node(const BVH_Node&) = delete;
		BVH_Node(BVH_Node&&) noexcept = delete;
		BVH_Node& operator=(const BVH_Node&) = delete;
		BVH_Node& operator=(BVH_Node&&) noexcept = delete;

		bool GetIsValid() const;

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

		FORCE_INLINE doom::physics::Collider* GetCollider()
		{
			return mCollider;
		}
		FORCE_INLINE doom::physics::Collider* GetCollider() const
		{
			return mCollider;
		}

		FORCE_INLINE const BVH<ColliderType>* GetOwnerBVH() const
		{
			return mOwnerBVH;
		}
	
		FORCE_INLINE const ColliderType& GetBoundingCollider() const
		{
			return mBoundingCollider;
		}

		FORCE_INLINE const ColliderType& GetEnlargedBoundingCollider() const
		{
			return mEnlargedBoundingCollider;
		}


		const BVH_Node<ColliderType>* GetParentNode() const;
		const BVH_Node<ColliderType>* GetLeftChildNode() const;
		const BVH_Node<ColliderType>* GetRightChildNode() const;

		int GetParentNodeIndex() const;
		int GetLeftChildNodeIndex() const;
		int GetRightChildNodeIndex() const;

		bool GetIsLeafNode() const;
		
		node_view_type UpdateNode();
	};

	

	using NodeCost = typename std::pair<int, float>;

	using BVH_Node2D = typename BVH_Node<doom::physics::AABB2D>;
	using BVH_Node3D = typename BVH_Node<doom::physics::AABB3D>;
	using BVH_NodeSphere = typename BVH_Node<doom::physics::Sphere>;

	extern template class BVH_Node<doom::physics::AABB2D>;
	extern template class BVH_Node<doom::physics::AABB3D>;
	extern template class BVH_Node<doom::physics::Sphere>;

	
}
