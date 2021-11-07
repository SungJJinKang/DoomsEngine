#pragma once

#include "KDTreeCore.h"

#include "Physics/Collider/AABB.h"
#include <Vector2.h>
#include <Vector3.h>

namespace dooms
{
	template <typename T>
	class KDTreeNodeView
	{
		friend class KDTree<T>;
		friend struct KDTreeNode<T>;

		using kd_tree_type = typename KDTree<T>;
		using node_type = typename KDTreeNode<T>;
		using this_type = typename KDTreeNodeView<T>;

	private:
		kd_tree_type* mKDTreePointer;
		INT32 mNodeIndex;

		constexpr KDTreeNodeView()
			:mKDTreePointer{ nullptr }, mNodeIndex{ NULL_NODE_INDEX }
		{

		}
		constexpr KDTreeNodeView(kd_tree_type* kdTreePointer, INT32 nodeIndex)
			: mKDTreePointer{ kdTreePointer }, mNodeIndex{ nodeIndex }
		{

		}

	public:

		constexpr KDTreeNodeView(const this_type&) = default;
		constexpr KDTreeNodeView(this_type&&) noexcept = default;
		constexpr this_type& operator=(const this_type&) = default;
		constexpr this_type& operator=(this_type&&) noexcept = default;

		typename node_type* operator->();
		constexpr INT32 GetNodeIndex()
		{
			return mNodeIndex;
		}

		constexpr bool IsValid()
		{
			return (mNodeIndex != NULL_NODE_INDEX) && (mKDTreePointer != nullptr);
		}
		constexpr operator bool()
		{
			return IsValid();
		}
		constexpr void Reset()
		{
			mKDTreePointer = nullptr;
			mNodeIndex = NULL_NODE_INDEX;
		}

	};

	using KDTreeView2DPoint = typename KDTree<math::Vector2>;
	using KDTreeView3DPoint = typename KDTree<math::Vector3>;
	//using KDTreeViewAABB3D = typename KDTree<physics::AABB3D>;

	//extern template class KDTreeNodeView<math::Vector2>;
	//extern template class KDTreeNodeView<math::Vector3>;
	//extern template class KDTreeNodeView<physics::AABB3D>;
	
}