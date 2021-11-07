#pragma once

namespace dooms
{
	
	struct TreeNode
	{
		INT32 mIndex;

		/// <summary>
		/// Node Index in BVH_Tree::mNodes
		/// </summary>
		INT32 mParentIndex;
		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		INT32 mLeftNode;

		/// <summary>
		/// Node index in BVH_Tree::mNodes
		/// </summary>
		INT32 mRightNode;
		
		bool bmIsActive;

		/// <summary>
		/// This variable will be used for various purpose
		/// 
		/// </summary>
		UINT32 mBitFlag;
		

		TreeNode() {}

		FORCE_INLINE UINT32 GetBitFlag() const
		{
			return mBitFlag;
		}
		FORCE_INLINE void ClearBitFlag()
		{
			mBitFlag = 0;
		}
		FORCE_INLINE void SetBitFlag(UINT32 bitflag)
		{
			mBitFlag |= bitflag;
		}
		
	};
}