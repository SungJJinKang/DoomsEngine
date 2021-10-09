#pragma once

// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION



#ifndef NEVER_HAPPEN
#define NEVER_HAPPEN __assume(0) // https://docs.microsoft.com/en-us/cpp/intrinsics/assume?view=msvc-160
#endif

#if defined(_MSC_VER)
#  define COMPILER_MSVC
#elif defined(__GNUC__)
#  define COMPILER_GCC
#endif

#if defined(COMPILER_GCC)
#  define FORCE_INLINE inline __attribute__ ((always_inline))
#  define NEVER_INLINE __attribute__ ((noinline))
#  define RESTRICT __restrict
#  define VLA_ARRAY_ON_STACK(type__, varname__, size__) type__ varname__[size__];
#elif defined(COMPILER_MSVC)
#  define FORCE_INLINE __forceinline
#  define NEVER_INLINE __declspec(noinline)
#  define RESTRICT __restrict
#  define VLA_ARRAY_ON_STACK(type__, varname__, size__) type__ *varname__ = (type__*)_alloca(size__ * sizeof(type__))
#endif


#ifndef EXIT_PROGRAM
#define EXIT_PROGRAM exit(0);
#endif

#include "DllMarcos.h"
#include "Path.h"
#include "Log.h"
#include "Assert.h"
#include "Profiling.h"
#include "KeyCallback.h"
