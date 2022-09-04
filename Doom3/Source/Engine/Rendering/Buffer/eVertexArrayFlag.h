#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum D_ENUM eVertexArrayFlag : UINT32
		{
			NONE = 0x0,
			VERTEX_VECTOR3 = 1 << 0,
			VERTEX_VECTOR2 = 1 << 1,
			TEXCOORD = 1 << 2,
			NORMAL = 1 << 3,
			TANGENT = 1 << 4,
			BI_TANGENT = 1 << 5,
			TBN = 1 << 6,
		};

		enum
		{
			VERTEX_ARRAY_FLAG_COUNT = 7
		};
	}
}
