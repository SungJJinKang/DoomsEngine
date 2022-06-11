#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		enum D_ENUM eCameraFlag : UINT32
		{
			IS_CULLED = 1 << 0,
			PAUSE_CULL_JOB = 1 << 1,
		};
	}
}
