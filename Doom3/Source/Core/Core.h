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

// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION

#include "Macros/Macros.h"

