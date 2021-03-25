#pragma once

#include "AccelerationBitFlag.h"

namespace doom
{
	
	class TreeNode
	{
	protected:

		int mIndex{ NULL_NODE_INDEX };

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

	public:

		
	};
}