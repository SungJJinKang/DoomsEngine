#pragma once

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include "BVH_Core.h"

namespace doom
{
	template <typename ColliderType>
	class BVH;
	template <typename ColliderType>
	struct BVH_Node;

	template <typename ColliderType>
	class BVH_Node_View
	{

	public:

		using bvh_type = typename BVH<ColliderType>;
		using node_type = typename BVH_Node<ColliderType>;
		using this_type = typename BVH_Node_View<ColliderType>;

	private:

		bvh_type* mOwnerBVH;
		int mNodeIndex;

	public:

		BVH_Node_View()
			:mOwnerBVH{ nullptr }, mNodeIndex{ NULL_NODE_INDEX }
		{

		}
		BVH_Node_View(bvh_type* const ownerBVH, const int nodeIndex)
			: mOwnerBVH{ ownerBVH }, mNodeIndex{ nodeIndex }
		{

		}
		
		BVH_Node_View(const this_type&) = default;
		BVH_Node_View(this_type&&) noexcept = default;
		this_type& operator=(const this_type&) = default;
		this_type& operator=(this_type&&) noexcept = default;

		typename node_type* operator->();
		const typename node_type* operator->() const;

		node_type* GetNode();
		const node_type* GetNode() const;

		int GetNodeIndex() const
		{
			return mNodeIndex;
		}

		bool IsValid() const
		{
			return (mNodeIndex != NULL_NODE_INDEX) && (mOwnerBVH != nullptr);
		}
		operator bool() const
		{
			return IsValid();
		}
		void Reset()
		{
			mOwnerBVH = nullptr;
			mNodeIndex = NULL_NODE_INDEX;
		}

	};

	using BVH_Node_View_AABB2D = typename BVH_Node_View<doom::physics::AABB2D>;
	using BVH_Node_View_AABB3D = typename BVH_Node_View<doom::physics::AABB3D>;
	using BVH_Node_View_Sphere = typename BVH_Node_View<doom::physics::Sphere>;

	extern template class BVH_Node_View<doom::physics::AABB2D>;
	extern template class BVH_Node_View<doom::physics::AABB3D>;
	extern template class BVH_Node_View<doom::physics::Sphere>;
}
