#pragma once

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include "BVH_Core.h"

namespace doom
{
	template <typename ColliderType>
	class BVH;
	template <typename ColliderType>
	class BVH_Node;

	template <typename ColliderType>
	class BVH_Node_View
	{
		friend class BVH<ColliderType>;
		friend class BVH_Node<ColliderType>;
		friend class BVH_Node_Container<ColliderType>;

		using bvh_type = typename BVH<ColliderType>;
		using node_type = typename BVH_Node<ColliderType>;
		using this_type = typename BVH_Node_View<ColliderType>;

	private:
		bvh_type* mOwnerBVH;
		int mNodeIndex;

		constexpr BVH_Node_View()
			:mOwnerBVH{ nullptr }, mNodeIndex{ NULL_NODE_INDEX }
		{

		}
		constexpr BVH_Node_View(bvh_type* ownerBVH, int nodeIndex)
			: mOwnerBVH{ ownerBVH }, mNodeIndex{ nodeIndex }
		{

		}

	public:
		
		constexpr BVH_Node_View(const this_type&) = default;
		constexpr BVH_Node_View(this_type&&) noexcept = default;
		constexpr this_type& operator=(const this_type&) = default;
		constexpr this_type& operator=(this_type&&) noexcept = default;

		typename node_type* operator->();
		constexpr int GetNodeIndex()
		{
			return this->mNodeIndex;
		}

		constexpr bool IsValid()
		{
			return (this->mNodeIndex != NULL_NODE_INDEX) && (this->mOwnerBVH != nullptr);
		}
		constexpr operator bool()
		{
			return this->IsValid();
		}
		constexpr void Reset()
		{
			this->mOwnerBVH = nullptr;
			this->mNodeIndex = NULL_NODE_INDEX;
		}

	};

	using BVH_Node_View_AABB2D = typename BVH_Node_View<doom::physics::AABB2D>;
	using BVH_Node_View_AABB3D = typename BVH_Node_View<doom::physics::AABB3D>;
	using BVH_Node_View_Sphere = typename BVH_Node_View<doom::physics::Sphere>;

	extern template class BVH_Node_View<doom::physics::AABB2D>;
	extern template class BVH_Node_View<doom::physics::AABB3D>;
	extern template class BVH_Node_View<doom::physics::Sphere>;
}
