#pragma once

#ifndef __AVX2__

#error "Please enable AVX2 option"

#endif

#include <iterator>
#include <immintrin.h>
#include <type_traits>
#include <cassert>
#include "builtin.h"


#if defined(__GNUC__)  || defined( __clang__)
#  define FAST_FIND_SIMD_FORCE_INLINE inline __attribute__ ((always_inline))
#  define FAST_FIND_SIMD_CURRENT_CPP_VERSION __cplusplus
#elif defined(_MSC_VER)
#  define FAST_FIND_SIMD_FORCE_INLINE __forceinline
#  define FAST_FIND_SIMD_CURRENT_CPP_VERSION _MSVC_LANG 
#endif

#if (FAST_FIND_SIMD_CURRENT_CPP_VERSION == 201703L) || (FAST_FIND_SIMD_CURRENT_CPP_VERSION == 202002L)
#define FAST_FIND_SIMD_CONSTEXPR constexpr
#else
#define FAST_FIND_SIMD_CONSTEXPR
#endif


namespace fast_find_simd
{
    // TODO : remove #include <type_traits>, implement custom is_scalar<T>

    namespace details
    {
        template<typename T, typename = void>
        struct is_iterator
        {
            static FAST_FIND_SIMD_CONSTEXPR bool value = false;
        };

        template<typename T>
        struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type>
        {
            static FAST_FIND_SIMD_CONSTEXPR const bool value = true;
        };
    }

    template <typename ITERATOR_TYPE>
    struct is_iteratype_type_find_simd_capable
    {
        static_assert(details::is_iterator<ITERATOR_TYPE>::value == true, "Please pass iterator type");

        using iterator_value_type = typename std::iterator_traits<ITERATOR_TYPE>::value_type;

        static FAST_FIND_SIMD_CONSTEXPR const bool value =
            (std::is_same<typename std::iterator_traits<ITERATOR_TYPE>::iterator_category, std::random_access_iterator_tag>::value == true) &&
            (std::is_scalar<iterator_value_type>::value == true) &&
            (sizeof(iterator_value_type) == 1 || sizeof(iterator_value_type) == 2 || sizeof(iterator_value_type) == 4 || sizeof(iterator_value_type) == 8)
    	;
    };

    namespace algo
    {
        template <const size_t valueSize>
        FAST_FIND_SIMD_FORCE_INLINE uintptr_t find_simd(const void* alignedCompareAddress, const void* const findValue)
        {
            static_assert(
                (valueSize == 1) ||
                (valueSize == 2) ||
                (valueSize == 4) ||
                (valueSize == 8),
                "unsupported type ( iterator's value type size should be 1 or 2 or 4 or 8 )"
            );
            return 0;
        }

        template <>
        FAST_FIND_SIMD_FORCE_INLINE uintptr_t find_simd<1>(const void* alignedCompareAddress, const void* const findValue)
        {
            const __m256i compareSIMDValue = _mm256_set1_epi8(*(char*)(findValue)); // maybe compiler will cache this variable.
            const __m256i cmp = _mm256_cmpeq_epi8(*(__m256i*)alignedCompareAddress, compareSIMDValue);
            const int z = _mm256_movemask_epi8(cmp);
            if (z)
            {
                const int first_1_pos = psnip_builtin_ffs(z) - 1;
                return (uintptr_t)alignedCompareAddress + (uintptr_t)first_1_pos;
            }

            return 0;
        }

        template <>
        FAST_FIND_SIMD_FORCE_INLINE uintptr_t find_simd<2>(const void* alignedCompareAddress, const void* const findValue)
        {
            const __m256i compareSIMDValue = _mm256_set1_epi16(*(short*)(findValue));
            const __m256i cmp = _mm256_cmpeq_epi16(*(__m256i*)alignedCompareAddress, compareSIMDValue);

            const __m256i inSlotShifted = _mm256_srli_epi16(cmp, 8);
            const int z = _mm256_movemask_epi8(inSlotShifted);
            if (z)
            {
                const int first_1_pos = psnip_builtin_ffs(z) - 1;
                return (uintptr_t)alignedCompareAddress + (((uintptr_t)first_1_pos >> 1) << 1);
            }

            return 0;
        }

        template <>
        FAST_FIND_SIMD_FORCE_INLINE uintptr_t find_simd<4>(const void* alignedCompareAddress, const void* const findValue)
        {
            const __m256i compareSIMDValue = _mm256_set1_epi32(*(int*)(findValue));
            const __m256i cmp = _mm256_cmpeq_epi32(*(__m256i*)alignedCompareAddress, compareSIMDValue);
            const int z = _mm256_movemask_ps(*(__m256*)(&cmp));
            if (z)
            {
                const int first_1_pos = psnip_builtin_ffs(z) - 1;
                return (uintptr_t)alignedCompareAddress + ((uintptr_t)first_1_pos << 2);
            }

            return 0;
        }

        template <>
        FAST_FIND_SIMD_FORCE_INLINE uintptr_t find_simd<8>(const void* alignedCompareAddress, const void* const findValue)
        {
            const __m256i compareSIMDValue = _mm256_set1_epi64x(*(long long*)(findValue));
            const __m256i cmp = _mm256_cmpeq_epi64(*(__m256i*)alignedCompareAddress, compareSIMDValue);
            const int z = _mm256_movemask_pd(*(__m256d*)(&cmp));
            if (z)
            {
                const int first_1_pos = psnip_builtin_ffs(z) - 1;
                return (uintptr_t)alignedCompareAddress + ((uintptr_t)first_1_pos << 3);
            }

            return 0;
        }       
    }
    

    template <typename LEGACY_RANDOM_ITERATOR>
    LEGACY_RANDOM_ITERATOR find_simd(LEGACY_RANDOM_ITERATOR beginIter, LEGACY_RANDOM_ITERATOR endIter, const typename std::add_const<typename std::iterator_traits<LEGACY_RANDOM_ITERATOR>::value_type>::type value)
    {
        static_assert(details::is_iterator<LEGACY_RANDOM_ITERATOR>::value == true, "Please pass iterator type");

        using iterator_value_type = typename std::iterator_traits<LEGACY_RANDOM_ITERATOR>::value_type;

        static_assert(std::is_same<typename std::iterator_traits<LEGACY_RANDOM_ITERATOR>::iterator_category, std::random_access_iterator_tag>::value == true, "unsupported type ( iterator should be random iterator )");

    	static_assert(std::is_scalar<iterator_value_type>::value == true, "unsupported type ( iterator's value type should be scalar type )");

        static_assert(
            (sizeof(iterator_value_type) == 1) ||
            (sizeof(iterator_value_type) == 2) ||
            (sizeof(iterator_value_type) == 4) ||
            (sizeof(iterator_value_type) == 8),
            "unsupported type ( iterator's value type size should be 1 or 2 or 4 or 8 )"
            );


        const iterator_value_type* compare = &(*beginIter);

        const iterator_value_type* const begin = compare;
        const iterator_value_type* const end = &(*(endIter - 1)) + 1; // dereferencing end iterator make assertion
        
        while ((compare != end) && ((((uintptr_t)(const void*)(compare)) % (32) == 0) == false))
        {// scalar compare until aligned to 32 byte ( AVX2, 256bit )
            if (*compare == value)
            {
                return beginIter + ((((uintptr_t)compare - (uintptr_t)begin) / sizeof(iterator_value_type)) + (((uintptr_t)compare - (uintptr_t)begin) % sizeof(iterator_value_type)));
            }
            compare++;
        }

        // now address in compare variable is aligned to 32 byte

        while (compare + (32 / sizeof(iterator_value_type)) <= end)
        {
            const uintptr_t resultAddress = algo::find_simd<sizeof(iterator_value_type)>(compare, &value);
            if (resultAddress != 0)
            {
                return beginIter + (resultAddress - (uintptr_t)begin) / sizeof(iterator_value_type);
            }
            compare += (32 / sizeof(iterator_value_type));
        }
        
        //scalar compare tails
        while (compare != end)
        {
            if (*compare == value)
            {
                return beginIter + ((((uintptr_t)compare - (uintptr_t)begin) / sizeof(iterator_value_type)) + (((uintptr_t)compare - (uintptr_t)begin) % sizeof(iterator_value_type)));
            }
            compare++;
        }

        return endIter;

    }



    /// <summary>
    /// find value from begin to end(excluded)
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="begin"></param>
    /// <param name="end"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    template <typename T>
    T* find_simd_raw(T* const begin, T* const end, T value)
    {
        static_assert(std::is_scalar<T>::value == true, "unsupported type ( value type should be scalar type )");

        static_assert(
            (sizeof(T) == 1) ||
            (sizeof(T) == 2) ||
            (sizeof(T) == 4) ||
            (sizeof(T) == 8),
            "unsupported type ( value type size should be 1 or 2 or 4 or 8 )"
            );

        assert(begin <= end);

        T* compare = begin;
        

        while ((compare != end) && ((((uintptr_t)(const void*)(compare)) % (32) == 0) == false))
        {// scalar compare until aligned to 32 byte ( AVX2, 256bit )
            if (*compare == value)
            {
                return compare;
            }
            compare++;
        }

        // now address in compare variable is aligned to 32 byte

        while (compare + (32 / sizeof(T)) <= end)
        {
            const uintptr_t resultAddress = algo::find_simd<sizeof(T)>(compare, &value);
            if (resultAddress != 0)
            {
                return (T*)resultAddress;
            }
            compare += (32 / sizeof(T));
        }

        //scalar compare tails
        while (compare != end)
        {
            if (*compare == value)
            {
                return compare;
            }
            compare++;
        }

        return end;

    }

    template <typename T>
    const T* find_simd_raw(const T* const begin, const T* const end, const T value)
    {
        return find_simd_raw(const_cast<T*>(begin), const_cast<T*>(end), value);
    }
}

