#pragma once

#include "../Reflection_RandomAccessIterator.h"
#include <Reflection/ReflectionType/ePropertyQualifier.h>

namespace dooms
{
	namespace reflection
	{
		class DType;
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
			/// <param name="typeFullName">for checking std::array element size ex) std::array<int, 12></param>
			/// <param name="dTemplateType"></param>
			/// <param name="iteratorIndex"></param>
			/// <returns></returns>
			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdArray
			(
				void* const std_array_ptr,
				const char* const typeFullName,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType,
				const size_t iteratorIndex
			);

			/// <summary>
			/// 
			/// </summary>
			/// <param name="std_array_ptr"></param>
			/// <param name="typeFullName">ex) for checking std::array element size std::array<int, 12></param>
			/// <param name="dTemplateType"></param>
			/// <param name="iteratorIndexType"></param>
			/// <returns></returns>
			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdArray
			(
				void* const std_array_ptr,
				const char* const typeFullName,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType,
				const eIteratorIndex iteratorIndexType
			);

			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdVector
			(
				void* const std_vector_ptr,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType,
				const size_t iteratorIndex
			);

			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_RandomAccessIterator_FromStdVector
			(
				void* const std_vector_ptr,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType,
				const eIteratorIndex iteratorIndexType
			);

			/// <summary>
			/// 
			/// </summary>
			/// <param name="std_container"></param>
			/// <param name="typeFullName">for checking std::array element size</param>
			/// <param name="dataQualifier"></param>
			/// <param name="dTemplateType"></param>
			/// <param name="iteratorIndex"></param>
			/// <returns></returns>
			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_Std_Container
			(
				void* const std_container,
				const char* const typeFullName,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType,
				const size_t iteratorIndex
			);

			/// <summary>
			/// 
			/// </summary>
			/// <param name="std_container"></param>
			/// <param name="typeFullName">for checking std::array element size</param>
			/// <param name="dataQualifier"></param>
			/// <param name="dTemplateType"></param>
			/// <param name="iteratorIndexType"></param>
			/// <returns></returns>
			dooms::reflection::Reflection_RandomAccessIterator Generate_Reflection_Std_Container
			(
				void* const std_container,
				const char* const typeFullName,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType,
				const eIteratorIndex iteratorIndexType
			);

			void* Generate_Reflection_smartPointer
			(
				void* const std_smartPointer,
				const reflection::eProperyQualifier dataQualifier,
				const DTemplateType& dTemplateType
			);
			
			eTemplateTypeCategory GetTempalteTypeCategory(const DTemplateType& dTemplateType);

			/// <summary>
			/// return template class's element type DType. ex) std::shared_ptr<!!!!!>, std::vector<!!>, std::array<!!, 15>
			/// </summary>
			/// <param name="dTemplateType"></param>
			/// <returns></returns>
			reflection::DType GetStdTemplateElementTypeDType(const DTemplateType& dTemplateType);

			/// <summary>
			/// return whether template class's element type is pointer type. ex) std::shared_ptr<int*> -> return true, std::vector<DObject*> -> return true
			/// </summary>
			/// <param name="dTemplateType"></param>
			/// <returns></returns>
			bool GetStdTemplateElementTypeIsPointer(const DTemplateType& dTemplateType);
		}
	}
}