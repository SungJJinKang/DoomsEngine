#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum D_ENUM eRenderingFlag : UINT32
		{
			STATIC_BATCH = 1 << 0,
			DYNAMIC_BATCH = 1 << 1
		};
	}
}