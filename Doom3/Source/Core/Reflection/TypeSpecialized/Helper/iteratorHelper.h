#pragma once

#include "../Reflection_RandomAccessIterator.h"

namespace dooms
{
	namespace reflection
	{
		class DTemplateType;
		struct Reflection_RandomAccessIterator;
		namespace helper
		{
			enum class eIteratorIndex
			{
				Begin,
				End
			};

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
		}
	}
}