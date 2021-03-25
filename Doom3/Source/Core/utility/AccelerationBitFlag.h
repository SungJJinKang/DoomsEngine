#pragma once

namespace doom
{
	enum class eAccelerationBitFlag : unsigned int
	{
		CullDistance = 1,
		ViewFustumCulling = 1 << 1,
	};

	class  AccelerationBitFlag
	{
	private:
		unsigned int mBitFlag{};

	public:
		inline void SetBitFlag(eAccelerationBitFlag bitflag)
		{
			mBitFlag |= static_cast<unsigned int>(bitflag);
		}
		inline void ClearBitFlag(eAccelerationBitFlag bitflag)
		{
			mBitFlag &= ~static_cast<unsigned int>(bitflag);
		}
		inline bool GetBitFlag(eAccelerationBitFlag bitflag)
		{
			return static_cast<bool>(this->mBitFlag & static_cast<unsigned int>(bitflag));
		}
	};
}