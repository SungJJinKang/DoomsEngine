#pragma once

#include <Core.h>

namespace dooms
{
	namespace thread
	{
		enum class D_ENUM eThreadType
		{
			GAME_THREAD,
			RENDER_THREAD,
			JOB_THREAD
			
		};
	}
}