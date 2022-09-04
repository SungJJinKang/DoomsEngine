#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum
		{
			MAX_VERTEX_BUFFER_LAYOUT_COUNT = 32
		};

		struct FVertexBufferLayout
		{
			UINT32 mStride;
			UINT32 mOffset;
		};
	}
}

			