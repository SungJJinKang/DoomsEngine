#pragma once

namespace doom
{
	
	class TreeNode
	{

	protected:

		int mIndex;

		/// <summary>
		/// Node Index in BVH_Tree::mNodes
		/// </summary>
		int mParentIndex;
		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mLeftNode;

		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		int mRightNode;
		
		bool bmIsActive;

		/// <summary>
		/// This variable will be used for various purpose
		/// 
		/// </summary>
		unsigned int mBitFlag;

	public:

		TreeNode() {}

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