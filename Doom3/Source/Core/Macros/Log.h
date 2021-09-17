#pragma once

#ifdef DEBUG_MODE
#include "../Logger/Logger.h"

#ifndef D_DEBUG_LOG
#define D_DEBUG_LOG(...)  doom::logger::Logger::Log(##__VA_ARGS__)
#endif

#else

#ifndef D_DEBUG_LOG
#define D_DEBUG_LOG(...)
#endif

#endif
