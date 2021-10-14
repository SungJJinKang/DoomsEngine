#pragma once

#include <Core.h>

constexpr inline INT32 NULL_NODE_INDEX{ -1 };

namespace doom
{
	template <typename T>
	class KDTree;

	template <typename T>
	struct KDTreeNode;

	template <typename T>
	class KDTreeNodeView;
}