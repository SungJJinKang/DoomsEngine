#pragma once

#include "EThreadType.h"

namespace dooms
{
	namespace thread
	{
		extern bool IsInGameThread();
		extern bool IsInRenderThread();
		extern EThreadType GetLocalThreadType();
	}
}
