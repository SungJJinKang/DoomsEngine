#pragma once


#ifdef _DEBUG
#define DEBUG_MODE
#else
#define RELEASE_MODE
#endif


#ifndef CPP_98_VERSION
#define CPP_98_VERSION 199711L
#endif

#ifndef CPP_11_VERSION
#define CPP_11_VERSION 201103L
#endif

#ifndef CPP_14_VERSION
#define CPP_14_VERSION 201402L
#endif

#ifndef CPP_17_VERSION
#define CPP_17_VERSION 201703L
#endif

#ifndef CPP_20_VERSION
#define CPP_20_VERSION 202002L
#endif


#if defined(__GNUC__)  || defined( __clang__)

#  define FORCE_INLINE inline __attribute__ ((always_inline))
#  define NEVER_INLINE __attribute__ ((noinline))
#  define RESTRICT __restrict
#  define VLA_ARRAY_ON_STACK(type__, varname__, size__) type__ varname__[size__];
#  define NO_DISCARD __attribute__((warn_unused_result))
#  define CURRENT_CPP_VERSION __cplusplus

#elif defined(_MSC_VER)
#  define FORCE_INLINE __forceinline
#  define NEVER_INLINE __declspec(noinline)
#  define RESTRICT __restrict
#  define VLA_ARRAY_ON_STACK(type__, varname__, size__) type__ *varname__ = (type__*)_alloca(size__ * sizeof(type__))
#  define NO_DISCARD [[nodiscard]]
#  define CURRENT_CPP_VERSION _MSVC_LANG 
#endif
 

#ifdef _WIN64

#ifndef OS_WIN64
#define OS_WIN64
#endif

#elif _WIN32

#ifndef OS_WIN32
#define OS_WIN32
#endif

#endif

#ifdef  DOOMS_ENGINE_DLL_EXPORT 
/*Enabled as "export" while compiling the dll project*/
#define DOOMS_ENGINE __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DOOMS_ENGINE __declspec(dllimport)  
#endif

