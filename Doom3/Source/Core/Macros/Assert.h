#pragma once
#include "Log.h"

#ifndef DEBUG_MODE // if not debug mode, don't throw assert
#define NDEBUG 
#endif
#include <cassert>
#ifndef NDEBUG
#include <iostream>
#   define D_ASSERT(condition) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

