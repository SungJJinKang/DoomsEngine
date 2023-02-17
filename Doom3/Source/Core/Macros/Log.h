#pragma once

#include <CompilerMacros.h>
#include "../Logger/Logger.h"

#ifndef ENABLE_DEBUG_LOG
#define ENABLE_DEBUG_LOG DEBUG_MODE
#endif

#ifndef ENABLE_RELEASE_LOG
#define ENABLE_RELEASE_LOG 1
#endif



#if ENABLE_DEBUG_LOG

#ifndef D_DEBUG_LOG
#define D_DEBUG_LOG(LOG_TYPE, ...) dooms::logger::Log(__FILE__, __LINE__, LOG_TYPE, ##__VA_ARGS__)
#endif

#ifndef D_DEBUG_CLOG
#define D_DEBUG_CLOG(CONDITION, LOG_TYPE, ...) if(CONDITION) dooms::logger::Log(__FILE__, __LINE__, LOG_TYPE, ##__VA_ARGS__)
#endif

#else

#ifndef D_DEBUG_LOG
#define D_DEBUG_LOG(...) do { } while (false)
#endif

#ifndef D_DEBUG_CLOG
#define D_DEBUG_CLOG(CONDITION, LOG_TYPE, ...) do { } while (false)
#endif

#endif



#if ENABLE_RELEASE_LOG

#ifndef D_RELEASE_LOG
#define D_RELEASE_LOG(LOG_TYPE, ...) dooms::logger::Log(__FILE__, __LINE__, LOG_TYPE, ##__VA_ARGS__)
#endif

#ifndef D_RELEASE_CLOG
#define D_RELEASE_CLOG(CONDITION, LOG_TYPE, ...) if(CONDITION) dooms::logger::Log(__FILE__, __LINE__, LOG_TYPE, ##__VA_ARGS__)
#endif

#else

#ifndef D_RELEASE_LOG
#define D_RELEASE_LOG(LOG_TYPE, ...) do { } while (false)
#endif

#ifndef D_RELEASE_CLOG
#define D_RELEASE_CLOG(CONDITION, LOG_TYPE, ...) do { } while (false)
#endif

#endif