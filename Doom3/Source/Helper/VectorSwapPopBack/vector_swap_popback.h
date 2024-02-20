#pragma once

#include <vector>
#include <algorithm>
#include "std_find_simd/fast_find_simd.h"


#if defined(__GNUC__)  || defined( __clang__)
#  define _VECTOR_SWAP_POPBACK_CURRENT_CPP_VERSION __cplusplus
#elif defined(_MSC_VER)
#  define _VECTOR_SWAP_POPBACK_CURRENT_CPP_VERSION _MSVC_LANG 
#endif

#if (_VECTOR_SWAP_POPBACK_CURRENT_CPP_VERSION == 201703L) || (_VECTOR_SWAP_POPBACK_CURRENT_CPP_VERSION == 202002L)
#define _VECTOR_SWAP_POPBACK_CONSTEXPR constexpr
#else
#define _VECTOR_SWAP_POPBACK_CONSTEXPR
#endif


namespace swap_popback
{
	/// <summary>
	/// /// How Work?? : 
	/// 
	/// This is how vector::erase works.
	/// 	1  2  3  4  5
	///
	///	1  X  3  4  5 (X is deleted element)
	/// 
	/// 	1 * *3  4  5 * *(element '3', '4', '5' is reallocated, this is sometimes too expensive)
	/// 
	///  How my library's vector_swap_popback works
	/// 
	/// 	1  2  3  4  5
	/// 
	/// 	1  X  3  4  5 (X is deleted element)
	/// 
	/// 	1 * *5 * *3  4  (only element '5' is reallocated)
	/// 
	/// 
	/// why iterator argument isn't supported?? : with iterator, should iterate to end element to find last element.
	/// but with index argument, can access to last element directly ( stl_vector internally has pointer of last elemet )
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	/// <param name="vector"></param>
	/// <param name="erasedElementIterator"></param>
	/// <returns>iterator at replaced element's new iterator, check with vector::end()</returns>
	template <typename T, typename Allocator>
	bool vector_swap_popback(std::vector<T, Allocator>& vector, typename std::vector<T, Allocator>::iterator targetIter)
	{
		if (vector.end() != targetIter)
		{
			std::iter_swap(targetIter, vector.end() - 1);
			vector.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T, typename Allocator>
	bool vector_find_swap_popback(std::vector<T, Allocator>& vector, const T& target)
	{
		typename std::vector<T, Allocator>::iterator targetIter;
		if _VECTOR_SWAP_POPBACK_CONSTEXPR (fast_find_simd::is_iteratype_type_find_simd_capable<typename std::vector<T, Allocator>::iterator>::value == false)
		{
			targetIter = std::find(vector.begin(), vector.end(), target);
		}
		else
		{
			targetIter = fast_find_simd::find_simd(vector.begin(), vector.end(), target);
		}

		if (targetIter != vector.end())
		{
			return vector_swap_popback(vector, targetIter);
		}
		else
		{
			return false;
		}
	}

	template <typename T, typename Allocator, typename Predicate>
	bool vector_find_if_swap_popback(std::vector<T, Allocator>& vector, const Predicate predicate)
	{
		typename std::vector<T, Allocator>::iterator targetIter = std::find_if(vector.begin(), vector.end(), predicate);
		
		if(targetIter != vector.end())
		{
			return vector_swap_popback(vector, targetIter);
		}
		else
		{
			return false;
		}
	}

}
