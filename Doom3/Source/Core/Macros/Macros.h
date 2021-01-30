#pragma once

#include "Path.h"
#include "Log.h"
#include "Assert.h"
#include "Profiling.h"

#ifdef DEBUG_MODE
# define NODEFAULT   D_ASSERT(0)
#else
# define NODEFAULT   __assume(0) // https://docs.microsoft.com/en-us/cpp/intrinsics/assume?view=msvc-160
#endif
