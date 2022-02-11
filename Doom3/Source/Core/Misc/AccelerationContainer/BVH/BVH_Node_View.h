#pragma once

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include "BVH_Core.h"
#include "BVH.h"

namespace dooms
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
		INT32 mNodeIndex;

	public:

		BVH_Node_View()
			:mOwnerBVH{ nullptr }, mNodeIndex{ NULL_NODE_INDEX }
		{

		}
		BVH_Node_View(bvh_type* const ownerBVH, const INT32 nodeIndex)
			: mOwnerBVH{ ownerBVH }, mNodeIndex{ nodeIndex }
		{

		}
		
		BVH_Node_View(const this_type&) = delete;
		BVH_Node_View(this_type&&) noexcept = default;
		this_type& operator=(const this_type&) = delete;
		this_type& operator=(this_type&&) noexcept = default;

		typename node_type* operator->();
		const typename node_type* operator->() const;

		FORCE_INLINE node_type* GetNode()
		{
			D_ASSERT(IsValid() == true);
			return mOwnerBVH->GetNode(mNodeIndex);
		}
		FORCE_INLINE const node_type* GetNode() const
		{
			D_ASSERT(IsValid() == true);
			return mOwnerBVH->GetNode(mNodeIndex);
		}

		INT32 GetNodeIndex() const
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

	//using BVH_Node_View_AABB2D = typename BVH_Node_View<dooms::physics::AABB2D>;
	using BVH_Node_View_AABB3D = typename BVH_Node_View<dooms::physics::AABB3D>;
	using BVH_Node_View_Sphere = typename BVH_Node_View<dooms::physics::Sphere>;

	//extern template class BVH_Node_View<dooms::physics::AABB2D>;
	extern template class BVH_Node_View<dooms::physics::AABB3D>;
	extern template class BVH_Node_View<dooms::physics::Sphere>;
}
