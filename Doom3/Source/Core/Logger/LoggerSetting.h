#pragma once

#include "eLogType.h"

namespace dooms
{
	namespace logger
	{
		inline extern eLogType MIN_DEBUG_LEVEL{ eLogType::D_LOG };
		inline extern eLogType MAX_DEBUG_LEVEL{ eLogType::D_LOG };
		inline extern bool BREAK_WHEN_ERROR{ false };
	}
}
