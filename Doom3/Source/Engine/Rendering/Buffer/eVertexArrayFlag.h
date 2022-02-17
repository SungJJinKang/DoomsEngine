#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum D_ENUM eVertexArrayFlag : UINT32
		{
			None = 0x0,
			VertexVector3 = 1 << 0,
			VertexVector2 = 1 << 1,
			TexCoord = 1 << 2,
			mNormal = 1 << 3,
			mTangent = 1 << 4,
			mBitangent = 1 << 5,
			mTBN = 1 << 6,
		};
	}
}
