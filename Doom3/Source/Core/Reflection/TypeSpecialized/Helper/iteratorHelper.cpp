#include "iteratorHelper.h"

#include <vector>


dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_RandomAccessIterator_FromStdVector
(
	void* const std_vector_ptr, 
	const DTemplateType& dTemplateType, 
	const size_t iteratorIndex
)
{
	std::vector<char>* fakeStdVector = reinterpret_cast<std::vector<char>*>(std_vector_ptr);

	const reflection::DTemplateArgumentType dTemplateTypeArgument = dTemplateType.GetTemplateArgumentType(0);

	D_ASSERT(dTemplateTypeArgument.IsValid() == true);

	const bool isVectorElementTypePointer = dTemplateTypeArgument.GetIsTemplateArgumentPointerType();

	const size_t typeSize = isVectorElementTypePointer == true ? sizeof(void*) : dTemplateTypeArgument.GetTypeSize();
	char* const ptr = reinterpret_cast<char*>(fakeStdVector->data()) + iteratorIndex * typeSize;

	return Reflection_RandomAccessIterator{ ptr, typeSize };
}

dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_RandomAccessIterator_FromStdVector
(
	void* const std_vector_ptr,
	const DTemplateType& dTemplateType,
	const eIteratorIndex iteratorIndex
)
{
	std::vector<char>* fakeStdVector = reinterpret_cast<std::vector<char>*>(std_vector_ptr);

	const reflection::DTemplateArgumentType dTemplateTypeArgument = dTemplateType.GetTemplateArgumentType(0);

	D_ASSERT(dTemplateTypeArgument.IsValid() == true);

	const bool isVectorElementTypePointer = dTemplateTypeArgument.GetIsTemplateArgumentPointerType();

	const size_t typeSize = isVectorElementTypePointer == true ? sizeof(void*) : dTemplateTypeArgument.GetTypeSize();
	char* ptr = reinterpret_cast<char*>(fakeStdVector->data());

	if(iteratorIndex == eIteratorIndex::End)
	{
		ptr += fakeStdVector->size();
	}

	return Reflection_RandomAccessIterator{ ptr, typeSize };
}
