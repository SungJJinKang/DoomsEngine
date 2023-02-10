#pragma once

#include <Core.h>

namespace dooms
{
	namespace thread
	{
		enum class EThreadType
		{
			GAME_THREAD,
			RENDER_THREAD,
			JOB_THREAD
			
		};
	}
}