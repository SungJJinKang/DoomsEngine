#pragma once

#include <CompilerMacros.h>


#ifdef DEBUG_MODE
#include "../Logger/Logger.h"

#ifndef D_DEBUG_LOG
#define D_DEBUG_LOG(LOG_TYPE, ...) dooms::logger::Log(__FILE__, __LINE__, LOG_TYPE, ##__VA_ARGS__)
#endif

#else

#ifndef D_DEBUG_LOG
#define D_DEBUG_LOG(...)
#endif

#endif
