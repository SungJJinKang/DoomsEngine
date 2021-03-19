#pragma once

#include "Core.h"

constexpr inline int NULL_NODE_INDEX{ -1 };

namespace doom
{
	template <int Dimension>
	class KDTree;

	template <int Dimension>
	struct KDTreeNode;

	template <int Dimension>
	class KDTreeNodeView;
}