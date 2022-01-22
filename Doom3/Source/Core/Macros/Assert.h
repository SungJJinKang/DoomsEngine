#pragma once

#include <CompilerMacros.h>

#ifndef NDEBUG
#include <cstdio>

#ifndef D_ASSERT

#   define D_ASSERT(condition) \
    do { \
        if (! (condition)) { \
            std::printf("Assertion `%s' failed in %s line %d :", #condition, __FILE__, __LINE__); \
            std::fflush(stdout); \
            std::terminate(); \
        } \
    } while (false)

#endif 

#ifndef D_ASSERT_LOG

#   define D_ASSERT_LOG(condition, MessageFormat, ...) \
    do { \
        if (! (condition)) { \
            std::printf("Assertion `%s' failed ( ", #condition); \
            std::printf(#MessageFormat, ##__VA_ARGS__); \
            std::printf(" ) in %s line %d :", __FILE__, __LINE__); \
            std::fflush(stdout); \
            std::terminate(); \
        } \
    } while (false)

#endif

#ifndef NEVER_HAPPEN
#define NEVER_HAPPEN D_ASSERT(0);
#endif


#else


#ifndef D_ASSERT
#define D_ASSERT(condition) do { } while (false)
#endif

#ifndef D_ASSERT_LOG
#define D_ASSERT_LOG(condition, MessageFormat, ...) do { } while (false)
#endif

#ifndef NEVER_HAPPEN
#define NEVER_HAPPEN __assume(0)
#endif

#endif

