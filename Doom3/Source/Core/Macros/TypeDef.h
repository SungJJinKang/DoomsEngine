#pragma once

#if (defined(COMPILER_MSVC) == false) && (defined(COMPILER_LLVM) == false)
#if _MSC_VER
#undef COMPILER_MSVC
#define COMPILER_MSVC
#else

#undef COMPILER_LLVM
#define COMPILER_LLVM
#endif
#endif

#ifdef COMPILER_MSVC
#include <intrin.h>
#elif COMPILER_LLVM
#include <x86intrin.h>
#else
#error SEE/NEON optimizations are not available for this compiler yet!!!!
#endif

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <float.h>

typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef INT32 BOOL32;

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef intptr_t INT_PTR;
typedef uintptr_t UINT_PTR;

typedef float FLOAT32;
typedef double DOUBLE;
typedef double FLOAT64;



/*
#define flag8(type) u8
#define flag16(type) u16
#define flag32(type) u32
#define flag64(type) u64

#define enum8(type) u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64
*/

#ifndef U8_MAX
#define U8_MAX 255
#endif


#ifndef U16_MAX
#define U16_MAX 65535
#endif


#ifndef INT32_MIN
#define INT32_MIN ((INT32)0x80000000)
#endif

#ifndef U16_MAX
#define INT32_MAX ((INT32)0x7fffffff)
#endif

#ifndef UINT32_MIN
#define UINT32_MIN 0
#endif


#ifndef UINT32_MAX
#define UINT32_MAX ((UINT32)-1)
#endif

#ifndef UINT64_MAX
#define UINT64_MAX ((UINT64)-1)
#endif

#ifndef FLOAT32_MAX
#define FLOAT32_MAX FLT_MAX
#endif

#ifndef FLOAT32_MIN
#define FLOAT32_MIN -FLT_MAX
#endif
