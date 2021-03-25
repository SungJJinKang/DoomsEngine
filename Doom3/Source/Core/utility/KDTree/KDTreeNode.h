#pragma once

#include "KDTreeCore.h"

#include <Vector2.h>
#include <Vector3.h>

#include "../TreeNode.h"

namespace doom
{
	template <int Dimension>
	struct KDTreeNode : public TreeNode, public AccelerationBitFlag
	{
		friend class KDTree_TestRoom;
		friend class KDTreeNodeView<Dimension>;

		using component_type = typename math::Vector<Dimension, float>;

		math::Vector<Dimension, float> mPoint;

	
		int mDimension{ NULL_NODE_INDEX };

		bool bmIsActive{ false };
	};

	using KDTreeNode2D = KDTreeNode<2>;
	using KDTreeNode3D = KDTreeNode<3>;
}