#pragma once
#include "Log.h"

#ifndef DEBUG_MODE // if not debug mode, don't throw assert

#ifndef NDEBUG
#define NDEBUG
#endif

#endif
#include <cassert>
#ifndef NDEBUG
#include <iostream>

#ifndef D_ASSERT
#   define D_ASSERT(condition) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#endif

#else

#ifndef D_ASSERT
#define D_ASSERT(condition) do { } while (false)
#endif

#endif

