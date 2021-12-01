#pragma once

#include <iterator>
#include <vector>

#include "Reflection/ReflectionType/DTemplateArgumentType.h"
#include "Reflection/ReflectionType/DTemplateType.h"

namespace dooms
{
	namespace reflection
	{

		struct Reflection_RandomAccessIterator
		{
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = char;
			using pointer = char*;
			using reference = char&;


			Reflection_RandomAccessIterator(char* const ptr, const size_t elementTypeSize)
				: m_ptr(ptr), m_TypeSize(elementTypeSize)
			{
			}


			reference operator*() const
			{
				return *m_ptr;
			}
			pointer operator->()
			{
				return m_ptr;
			}
			Reflection_RandomAccessIterator& operator++()
			{
				m_ptr += m_TypeSize;
				return *this;
			}
			Reflection_RandomAccessIterator operator++(int)
			{
				Reflection_RandomAccessIterator tmp = *this;
				++(*this);
				return tmp;
			}
			Reflection_RandomAccessIterator operator+=(const size_t count)
			{
				m_ptr += m_TypeSize * count;
				return *this;
			}
			Reflection_RandomAccessIterator& operator--()
			{
				m_ptr -= m_TypeSize;
				return *this;
			}
			Reflection_RandomAccessIterator operator--(int)
			{
				Reflection_RandomAccessIterator tmp = *this;
				--(*this);
				return tmp;
			}
			Reflection_RandomAccessIterator operator-=(const size_t count)
			{
				m_ptr -= m_TypeSize * count;
				return *this;
			}
			friend bool operator== (const Reflection_RandomAccessIterator& a, const Reflection_RandomAccessIterator& b)
			{
				return a.m_ptr == b.m_ptr;
			};
			friend bool operator!= (const Reflection_RandomAccessIterator& a, const Reflection_RandomAccessIterator& b)
			{
				return a.m_ptr != b.m_ptr;
			};


		private:

			pointer m_ptr;
			size_t m_TypeSize;
		};

	}
}

