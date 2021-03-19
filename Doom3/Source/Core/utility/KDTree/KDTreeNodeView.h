#pragma once

#include "KDTreeCore.h"

namespace doom
{
	template <int Dimension>
	class KDTreeNodeView
	{
		friend class KDTree<Dimension>;
		friend struct KDTreeNode<Dimension>;

		using node_type = typename KDTreeNode<Dimension>;
		using this_type = typename KDTreeNodeView<Dimension>;

	private:
		node_type** mNodeArrayPointer;
		int mNodeIndex;

		constexpr KDTreeNodeView()
			:mNodeArrayPointer{ nullptr }, mNodeIndex{ NULL_NODE_INDEX }
		{

		}
		constexpr KDTreeNodeView(node_type** nodeArrayPointer, int nodeIndex)
			: mNodeArrayPointer{ nodeArrayPointer }, mNodeIndex{ nodeIndex }
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
			return (this->mNodeIndex != NULL_NODE_INDEX) && (this->mNodeArrayPointer != nullptr);
		}
		constexpr operator bool()
		{
			return this->IsValid();
		}
		constexpr void Reset()
		{
			this->mNodeArrayPointer = nullptr;
			this->mNodeIndex = NULL_NODE_INDEX;
		}

	};

	using KDTreeNodeView_2D = typename KDTreeNodeView<2>;
	using KDTreeNodeView_3D = typename KDTreeNodeView<3>;

	extern template class KDTreeNodeView<2>;
	extern template class KDTreeNodeView<3>;
	
}