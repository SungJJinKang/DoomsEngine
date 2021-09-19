#pragma once

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
		
		bool bmIsActive{ false };

		/// <summary>
		/// This variable will be used for various purpose
		/// 
		/// </summary>
		unsigned int mBitFlag;

	public:

		FORCE_INLINE unsigned int GetBitFlag() const
		{
			return mBitFlag;
		}
		FORCE_INLINE void ClearBitFlag()
		{
			mBitFlag = 0;
		}
		FORCE_INLINE void SetBitFlag(unsigned int bitflag)
		{
			mBitFlag |= bitflag;
		}
		
	};
}