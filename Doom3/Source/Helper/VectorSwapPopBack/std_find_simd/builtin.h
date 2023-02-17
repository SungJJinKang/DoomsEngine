#pragma once
/* Builtins and Intrinsics
 * Portable Snippets - https://github.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Some of these implementations are based on code from
 * https://graphics.stanford.edu/~seander/bithacks.html which is also
 * public domain (and a fantastic web site).
 */

#if !defined(FAST_FIND_SIMD_PSNIP_BUILTIN_H)
#define FAST_FIND_SIMD_PSNIP_BUILTIN_H

#if defined(HEDLEY_GCC_HAS_BUILTIN)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) HEDLEY_GCC_HAS_BUILTIN(builtin,major,minor,0)
#elif defined(__clang__) && defined(__has_builtin)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) __has_builtin(builtin)
#elif defined(__GNUC__)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (__GNUC__ > major || (major == __GNUC__ && __GNUC_MINOR__ >= minor))
#else
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (0)
#endif

#if defined(HEDLEY_CLANG_HAS_BUILTIN)
#  define PSNIP_BUILTIN_CLANG_HAS_BUILTIN(builtin) HEDLEY_CLANG_HAS_BUILTIN(builtin)
#elif defined(__has_builtin)
#  define PSNIP_BUILTIN_CLANG_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define PSNIP_BUILTIN_CLANG_HAS_BUILTIN(builtin) (0)
#endif

#if defined(HEDLEY_MSVC_VERSION_CHECK)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) HEDLEY_MSVC_VERSION_CHECK(major,minor,0)
#elif !defined(_MSC_VER)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (0)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_FULL_VER >= ((major * 100000) + (minor * 1000)))
#else
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_VER >= ((major * 100) + (minor)))
#endif

#if defined(_MSC_VER)
#  include <intrin.h>
#endif
#include <limits.h>
#include <stdlib.h>

#if defined(__i386) || defined(_M_IX86) || \
  defined(__amd64) || defined(_M_AMD64) || defined(__x86_64)
#  if defined(_MSC_VER)
#    define PSNIP_BUILTIN__ENABLE_X86
#  elif defined(__GNUC__)
#    define PSNIP_BUILTIN__ENABLE_X86
#    include <x86intrin.h>
#  endif
#endif

#if defined(__amd64) || defined(_M_AMD64) || defined(__x86_64)
#  if defined(_MSC_VER)
#    define PSNIP_BUILTIN__ENABLE_AMD64
#  elif defined(__GNUC__)
#    define PSNIP_BUILTIN__ENABLE_AMD64
#    include <x86intrin.h>
#  endif
#endif

#if defined(__ARM_ACLE)
#  include <arm_acle.h>
#endif

#if !defined(PSNIP_BUILTIN_STATIC_INLINE)
#  if defined(__GNUC__)
#    define PSNIP_BUILTIN__COMPILER_ATTRIBUTES __attribute__((__unused__))
#  else
#    define PSNIP_BUILTIN__COMPILER_ATTRIBUTES
#  endif

#  if defined(HEDLEY_INLINE)
#    define PSNIP_BUILTIN__INLINE HEDLEY_INLINE
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define PSNIP_BUILTIN__INLINE inline
#  elif defined(__GNUC_STDC_INLINE__)
#    define PSNIP_BUILTIN__INLINE __inline__
#  elif defined(_MSC_VER) && _MSC_VER >= 1200
#    define PSNIP_BUILTIN__INLINE __inline
#  else
#    define PSNIP_BUILTIN__INLINE
#  endif

#  define PSNIP_BUILTIN__FUNCTION PSNIP_BUILTIN__COMPILER_ATTRIBUTES static PSNIP_BUILTIN__INLINE
#endif

    /******
     *** GCC-style built-ins
     ******/

     /*** __builtin_ffs ***/

#define PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(f_n, T)	\
  PSNIP_BUILTIN__FUNCTION				\
  int psnip_builtin_##f_n(T x) {			\
    static const char psnip_builtin_ffs_lookup[256] = { \
      0, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      8, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1	\
    };							\
							\
    unsigned char t;					\
    size_t s = 0;					\
							\
    while (s < (sizeof(T) * 8)) {			\
      t = (unsigned char) ((x >> s) & 0xff);		\
      if (t)						\
        return psnip_builtin_ffs_lookup[t] + s;		\
							\
      s += 8;						\
    }							\
							\
    return 0;						\
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ffs, 3, 3)
#  define psnip_builtin_ffs(x)   __builtin_ffs(x)
#  define psnip_builtin_ffsl(x)  __builtin_ffsl(x)
#  define psnip_builtin_ffsll(x) __builtin_ffsll(x)
#  define psnip_builtin_ffs32(x) PSNIP_BUILTIN__VARIANT_INT32(_,ffs)(x)
#  define psnip_builtin_ffs64(x) PSNIP_BUILTIN__VARIANT_INT64(_,ffs)(x)
#else
#  if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanForward, 14, 0)
PSNIP_BUILTIN__FUNCTION
int psnip_builtin_ffsll(long long v) {
    unsigned long r;
#    if defined(_M_AMD64) || defined(_M_ARM)
    if (_BitScanForward64(&r, (unsigned long long) v)) {
        return (int)(r + 1);
    }
#    else
    if (_BitScanForward(&r, (unsigned long)(v))) {
        return (int)(r + 1);
    }
    else if (_BitScanForward(&r, (unsigned long)(v >> 32))) {
        return (int)(r + 33);
    }
#    endif
    return 0;
}

PSNIP_BUILTIN__FUNCTION
int psnip_builtin_ffsl(long v) {
    unsigned long r;
    if (_BitScanForward(&r, (unsigned long)v)) {
        return (int)(r + 1);
    }
    return 0;
}

PSNIP_BUILTIN__FUNCTION
int psnip_builtin_ffs(int v) {
    return psnip_builtin_ffsl(v);
}
#  else
PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffs, int)
PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffsl, long)
PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffsll, long long)
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_ffsll(v) psnip_builtin_ffsll(v)
#    define __builtin_ffsl(v)  psnip_builtin_ffsl(v)
#    define __builtin_ffs(v)   psnip_builtin_ffs(v)
#  endif
#endif

#if !defined(psnip_builtin_ffs32)
#  define psnip_builtin_ffs32(x) PSNIP_BUILTIN__VARIANT_INT32(psnip,ffs)(x)
#endif

#if !defined(psnip_builtin_ffs64)
#  define psnip_builtin_ffs64(x) PSNIP_BUILTIN__VARIANT_INT64(psnip,ffs)(x)
#endif

#endif