#pragma once

#include "KDTreeCore.h"

namespace doom
{
	template <typename T>
	class KDTreeNodeView
	{
		friend class KDTree<Dimension>;
		friend struct KDTreeNode<Dimension>;

		using kd_tree_type = typename KDTree<Dimension>;
		using node_type = typename KDTreeNode<Dimension>;
		using this_type = typename KDTreeNodeView<Dimension>;

	private:
		kd_tree_type* mKDTreePointer;
		int mNodeIndex;

		constexpr KDTreeNodeView()
			:mKDTreePointer{ nullptr }, mNodeIndex{ NULL_NODE_INDEX }
		{

		}
		constexpr KDTreeNodeView(kd_tree_type* kdTreePointer, int nodeIndex)
			: mKDTreePointer{ kdTreePointer }, mNodeIndex{ nodeIndex }
		{

		}

	public:

		constexpr KDTreeNodeView(const this_type&) = default;
		constexpr KDTreeNodeView(this_type&&) noexcept = default;
		constexpr this_type& operator=(const this_type&) = default;
		constexpr this_type& operator=(this_type&&) noexcept = default;

		typename node_type* operator->();
		constexpr int GetNodeIndex()
		{
			return this->mNodeIndex;
		}

		constexpr bool IsValid()
		{
			return (this->mNodeIndex != NULL_NODE_INDEX) && (this->mKDTreePointer != nullptr);
		}
		constexpr operator bool()
		{
			return this->IsValid();
		}
		constexpr void Reset()
		{
			this->mKDTreePointer = nullptr;
			this->mNodeIndex = NULL_NODE_INDEX;
		}

	};

	using KDTreeView2DPoint = typename KDTree<math::Vector2>;
	using KDTreeView3DPoint = typename KDTree<math::Vector3>;
	using KDTreeViewAABB3D = typename KDTree<physics::AABB3D>;

	extern template class KDTreeNodeView<math::Vector2>;
	extern template class KDTreeNodeView<math::Vector3>;
	extern template class KDTreeNodeView<physics::AABB3D>;
	
}