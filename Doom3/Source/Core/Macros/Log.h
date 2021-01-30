#pragma once

#ifdef DEBUG_MODE
#include "../Log/Logger.h"
#define D_DEBUG_LOG(...)  doom::logger::Log(##__VA_ARGS__)
#else
#define D_DEBUG_LOG(...)
#endif
