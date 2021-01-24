#pragma once
#include "../Log/Logger.h"
#ifdef DEBUG_MODE
#define DEBUG_LOG(...)  doom::log::Logger.Log(##__VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif
