#pragma once

#ifdef DEBUG_MODE
#include "../Logger/Logger.h"
#define D_DEBUG_LOG(...)  doom::logger::Debug::Log(##__VA_ARGS__)
#else
#define D_DEBUG_LOG(...)
#endif
