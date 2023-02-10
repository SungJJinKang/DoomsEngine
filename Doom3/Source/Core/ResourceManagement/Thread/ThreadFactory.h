#pragma once

#include <Core.h>
#include "EThreadType.h"

namespace dooms
{
	namespace thread
	{
		class RunnableThread;
		namespace ThreadFactory
		{
			RunnableThread* CreateRunnableThread(const EThreadType TargetThreadType);
		}
	}
}

