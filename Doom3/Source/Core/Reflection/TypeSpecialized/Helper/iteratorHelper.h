#pragma once

#include "../Reflection_RandomAccessIterator.h"

namespace dooms
{
	namespace reflection
	{
		class DTemplateType;
		struct Reflection_RandomAccessIterator;

		enum class eTemplateTypeCategory
		{
			None,
			SmartPointer,
			RandomAccessIterator
		};

		namespace helper
		{
			enum class eIteratorIndex
			{
				Begin,
				End
			};

			
			
			/// <summary>
			/// 
			/// </summary>
			/// <param name="std_array_ptr"></param>
			/// <param name="typeFullName">ex) std::array<int, 12></param>
			/// <param name="dTemplateType"></param>
			/// <param name="iteratorIndex"></param>
			/// <returns></returns>
			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdArray
			(
				void* const std_array_ptr,
				const char* const typeFullName,
				const DTemplateType& dTemplateType,
				const size_t iteratorIndex
			);

			/// <summary>
			/// 
			/// </summary>
			/// <param name="std_array_ptr"></param>
			/// <param name="typeFullName">ex) std::array<int, 12></param>
			/// <param name="dTemplateType"></param>
			/// <param name="iteratorIndexType"></param>
			/// <returns></returns>
			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdArray
			(
				void* const std_array_ptr,
				const char* const typeFullName,
				const DTemplateType& dTemplateType,
				const eIteratorIndex iteratorIndexType
			);

			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdVector
			(
				void* const std_vector_ptr,
				const DTemplateType& dTemplateType,
				const size_t iteratorIndex
			);

			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdVector
			(
				void* const std_vector_ptr,
				const DTemplateType& dTemplateType,
				const eIteratorIndex iteratorIndexType
			);

			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_Std_Container
			(
				void* const std_container,
				const DTemplateType& dTemplateType,
				const size_t iteratorIndex
			);

			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_Std_Container
			(
				void* const std_container,
				const DTemplateType& dTemplateType,
				const eIteratorIndex iteratorIndexType
			);

			eTemplateTypeCategory GetTempalteTypeCategory(const DTemplateType& dTemplateType);
		}
	}
}