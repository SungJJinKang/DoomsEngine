#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum D_ENUM eVertexArrayFlag : UINT32
		{
			None = 0x0,
			VertexVector3 = 1,
			VertexVector2 = 2,
			TexCoord = 4,
			mNormal = 8,
			mTangent = 16,
			mBitangent = 32,
		};
	}
}
