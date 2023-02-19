#pragma once

#include "eLogType.h"

namespace dooms
{
	namespace logger
	{
		inline extern eLogType MIN_DEBUG_LEVEL{ eLogType::D_LOG };
		inline extern eLogType MAX_DEBUG_LEVEL{ eLogType::D_LOG };
		inline extern bool BREAK_WHEN_ERROR{ false };
		inline extern bool SCROLL_TO_BOTTOM{ true };
		inline extern bool PRINT_LOG_CODE_LOCATION{ false };
	}
}
