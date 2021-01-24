#pragma once


#ifdef _DEBUG
#define DEBUG_MODE
#else
#define BUILD_MODE
#endif

#ifdef DEBUG_MODE
#define ONLY_DEBUG(...) __VA_ARGS__
#elif BUILD_MODE
#define ONLY_DEBUG(...)
#endif

#include "Macros/Macros.h"