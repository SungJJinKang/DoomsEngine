#include "iteratorHelper.h"

#include <array>
#include <vector>


dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_RandomAccessIterator_FromStdArray
(
	void* const std_array_ptr,
	const char* const typeFullName,
	const DTemplateType& dTemplateType,
	const size_t iteratorIndex
)
{
	D_ASSERT(std_array_ptr != nullptr);
	
	const reflection::DTemplateArgumentType dTemplateTypeArgument = dTemplateType.GetTemplateArgumentType(0);

	D_ASSERT(dTemplateTypeArgument.IsValid() == true);
	
	std::array<char, 1>* fakeArray = reinterpret_cast<std::array<char, 1>*>(std_array_ptr);

	const size_t arrayElementTypeSize = (dTemplateTypeArgument.GetIsTemplateArgumentPointerType() == true) ? sizeof(void*) : dTemplateTypeArgument.GetTypeSize();
	char* const ptr = reinterpret_cast<char*>(fakeArray->data()) + iteratorIndex * arrayElementTypeSize;

	return Reflection_RandomAccessIterator{ ptr, arrayElementTypeSize };
}

dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_RandomAccessIterator_FromStdArray\
(
	void* const std_array_ptr,
	const char* const typeFullName,
	const DTemplateType& dTemplateType,
	const eIteratorIndex iteratorIndexType
)
{
	D_ASSERT(std_array_ptr != nullptr);

	const reflection::DTemplateArgumentType dTemplateTypeArgument = dTemplateType.GetTemplateArgumentType(0);

	D_ASSERT(dTemplateTypeArgument.IsValid() == true);

	std::array<char, 1>* fakeArray = reinterpret_cast<std::array<char, 1>*>(std_array_ptr);

	const size_t arrayElementTypeSize = (dTemplateTypeArgument.GetIsTemplateArgumentPointerType() == true) ? sizeof(void*) : dTemplateTypeArgument.GetTypeSize();
	char* ptr = reinterpret_cast<char*>(fakeArray->data());

	if (iteratorIndexType == eIteratorIndex::End)
	{
		const std::string_view typeFullNameStringView = typeFullName;
		const size_t lastTemplateArgumentComma = typeFullNameStringView.find_last_of(',');
		const size_t lastTemplateCloseBlancket = typeFullNameStringView.find_last_of('>');

		D_ASSERT(lastTemplateArgumentComma != std::string::npos && lastTemplateCloseBlancket != std::string::npos);

		const std::string stdArraySizeTemplateArgumentString
		{
			typeFullNameStringView.begin() + lastTemplateArgumentComma + 1,
			typeFullNameStringView.begin() + lastTemplateCloseBlancket
		};

		char* pos = NULL;
		const size_t vectorElementRealCount = strtoll(stdArraySizeTemplateArgumentString.c_str(), &pos, 10);

		ptr += vectorElementRealCount * arrayElementTypeSize;
	}

	return Reflection_RandomAccessIterator{ ptr, arrayElementTypeSize };
}

dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_RandomAccessIterator_FromStdVector
(
	void* const std_vector_ptr, 
	const DTemplateType& dTemplateType, 
	const size_t iteratorIndex
)
{
	D_ASSERT(std_vector_ptr != nullptr);

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
	D_ASSERT(std_vector_ptr != nullptr);

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

dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_Std_Container
(
	void* const std_container, 
	const DTemplateType& dTemplateType, 
	const size_t iteratorIndex)
{
	return dooms::reflection::Reflection_RandomAccessIterator{ nullptr, 0 };
}

dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_Std_Container
(
	void* const std_container, 
	const DTemplateType& dTemplateType, 
	const eIteratorIndex iteratorIndexType
)
{
	return dooms::reflection::Reflection_RandomAccessIterator{nullptr, 0};
}

dooms::reflection::helper::eTemplateClassType dooms::reflection::helper::GetTempalteTypeCategory(const DTemplateType& dTemplateType)
{
	std::string templateTypeName = dTemplateType.GetTemplateTypeName();

}
