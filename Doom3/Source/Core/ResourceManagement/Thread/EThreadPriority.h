#pragma once

#include <Core.h>

namespace dooms
{
	namespace thread
	{
		enum class EThreadPriority
		{
			High,
			Middle,
			Low,
			Background
		};

		extern const char* GetThreadPriorityNameStr(const EThreadPriority InThreadPriority);
	}
}