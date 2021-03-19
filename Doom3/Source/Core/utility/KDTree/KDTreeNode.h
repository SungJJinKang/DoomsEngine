#pragma once

#include "KDTreeCore.h"

#include <Vector2.h>
#include <Vector3.h>

namespace doom
{
	template <int Dimension>
	struct KDTreeNode
	{
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
		int mChild1{ NULL_NODE_INDEX };

		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mChild2{ NULL_NODE_INDEX };
	};

	using KDTreeNode_2D = KDTreeNode<2>;
	using KDTreeNode_3D = KDTreeNode<3>;
}