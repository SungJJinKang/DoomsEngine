#pragma once

#include "KDTreeCore.h"

#include <Vector2.h>
#include <Vector3.h>

namespace doom
{
	template <int Dimension>
	struct KDTreeNode
	{
		friend class KDTree_TestRoom;
		friend class KDTreeNodeView<Dimension>;

		using component_type = typename math::Vector<Dimension, float>;

		math::Vector<Dimension, float> mPoint;

		/// <summary>
		/// Don't change this except in AllocateNewNode
		/// </summary>
		int mIndex{ NULL_NODE_INDEX };
		int mDimension{ NULL_NODE_INDEX };

		bool bmIsActive{ false };

		/// <summary>
		/// Node Index in BVH_Tree::mNodes
		/// </summary>
		int mParentIndex{ NULL_NODE_INDEX };
		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mLeftNode{ NULL_NODE_INDEX };

		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mRightNode{ NULL_NODE_INDEX };
	};

	using KDTreeNode2D = KDTreeNode<2>;
	using KDTreeNode3D = KDTreeNode<3>;
}