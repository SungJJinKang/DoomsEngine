#pragma once

// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION

#include "Path.h"
#include "Log.h"
#include "Assert.h"
#include "Profiling.h"

#ifdef DEBUG_MODE
# define NODEFAULT   D_ASSERT(0)
#else
# define NODEFAULT   __assume(0) // https://docs.microsoft.com/en-us/cpp/intrinsics/assume?view=msvc-160
#endif

