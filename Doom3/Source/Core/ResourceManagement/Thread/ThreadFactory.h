#pragma once

#include <Core.h>
#include "eThreadType.h"

namespace dooms
{
	namespace thread
	{
		class RunnableThread;
		namespace ThreadFactory
		{
			RunnableThread* CreateRunnableThread(const eThreadType TargetThreadType);
		}
	}
}

