#include "iteratorHelper.h"

#include <array>
#include <vector>
#include <memory>


dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_RandomAccessIterator_FromStdArray
(
	void* const std_array_ptr,
	const char* const typeFullName,
	const reflection::eProperyQualifier dataQualifier,
	const DTemplateType& dTemplateType,
	const size_t iteratorIndex
)
{
	D_ASSERT(std_array_ptr != nullptr);
	D_ASSERT(GetTempalteTypeCategory(dTemplateType) == eTemplateTypeCategory::RandomAccessIterator);
	D_ASSERT_LOG(dataQualifier == eProperyQualifier::VALUE, "not supported data type");

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
	const reflection::eProperyQualifier dataQualifier,
	const DTemplateType& dTemplateType,
	const eIteratorIndex iteratorIndexType
)
{
	D_ASSERT(std_array_ptr != nullptr);
	D_ASSERT(GetTempalteTypeCategory(dTemplateType) == eTemplateTypeCategory::RandomAccessIterator);
	D_ASSERT_LOG(dataQualifier == eProperyQualifier::VALUE, "not supported data type");

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
	const reflection::eProperyQualifier dataQualifier,
	const DTemplateType& dTemplateType, 
	const size_t iteratorIndex
)
{
	D_ASSERT(std_vector_ptr != nullptr);
	D_ASSERT(GetTempalteTypeCategory(dTemplateType) == eTemplateTypeCategory::RandomAccessIterator);
	D_ASSERT_LOG(dataQualifier == eProperyQualifier::VALUE, "not supported data type");

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
	const reflection::eProperyQualifier dataQualifier,
	const DTemplateType& dTemplateType,
	const eIteratorIndex iteratorIndex
)
{
	D_ASSERT(std_vector_ptr != nullptr);
	D_ASSERT(GetTempalteTypeCategory(dTemplateType) == eTemplateTypeCategory::RandomAccessIterator);
	D_ASSERT_LOG(dataQualifier == eProperyQualifier::VALUE, "not supported data type");

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
	const char* const typeFullName,
	const reflection::eProperyQualifier dataQualifier,
	const DTemplateType& dTemplateType, 
	const size_t iteratorIndex)
{
	const std::string templateTypeName = dTemplateType.GetTemplateTypeName();

	dooms::reflection::Reflection_RandomAccessIterator iter;

	if (templateTypeName == "std::vector")
	{
		iter = Generate_Reflection_RandomAccessIterator_FromStdVector(std_container, dataQualifier, dTemplateType, iteratorIndex);
	}
	else if(templateTypeName == "std::array")
	{
		iter = Generate_Reflection_RandomAccessIterator_FromStdArray(std_container, typeFullName, dataQualifier, dTemplateType, iteratorIndex);
	}
	else
	{
		D_ASSERT_LOG(false, "currently not supported container type");
	}

	// if std::vector's size is 0, iter::m_ptr can be 0
	//D_ASSERT(iter == true);

	return iter;
}

dooms::reflection::Reflection_RandomAccessIterator dooms::reflection::helper::Generate_Reflection_Std_Container
(
	void* const std_container,
	const char* const typeFullName,
	const reflection::eProperyQualifier dataQualifier,
	const DTemplateType& dTemplateType, 
	const eIteratorIndex iteratorIndexType
)
{
	const std::string templateTypeName = dTemplateType.GetTemplateTypeName();

	dooms::reflection::Reflection_RandomAccessIterator iter{};

	if (templateTypeName == "std::vector")
	{
		iter = Generate_Reflection_RandomAccessIterator_FromStdVector(std_container, dataQualifier, dTemplateType, iteratorIndexType);
	}
	else if (templateTypeName == "std::array")
	{
		iter = Generate_Reflection_RandomAccessIterator_FromStdArray(std_container, typeFullName, dataQualifier, dTemplateType, iteratorIndexType);
	}
	else
	{
		D_ASSERT_LOG(false, "currently not supported container type");
	}

	// if std::vector's size is 0, iter::m_ptr can be 0
	//D_ASSERT(iter == true);

	return iter;
}

void* dooms::reflection::helper::Generate_Reflection_smartPointer
(
	void* const std_smartPointer,
	const reflection::eProperyQualifier dataQualifier, 
	const DTemplateType& dTemplateType)
{
	D_ASSERT(std_smartPointer != nullptr);
	D_ASSERT(GetTempalteTypeCategory(dTemplateType) == eTemplateTypeCategory::SmartPointer);
	D_ASSERT_LOG(dataQualifier == eProperyQualifier::VALUE, "not supported data type");


	void* StoredObjectPointer = nullptr;

	const std::string templateTypeName = dTemplateType.GetTemplateTypeName();
	
	if (templateTypeName == "std::unique_ptr")
	{
		std::unique_ptr<char>* const smart_ptr = reinterpret_cast<std::unique_ptr<char>*>(std_smartPointer);
		if(smart_ptr)
		{
			StoredObjectPointer = smart_ptr->get();
		}
	}
	else if(templateTypeName == "std::shared_ptr")
	{
		std::shared_ptr<char>* const smart_ptr = reinterpret_cast<std::shared_ptr<char>*>(std_smartPointer);
		if (smart_ptr)
		{
			StoredObjectPointer = smart_ptr->get();
		}
	}

	return StoredObjectPointer;
}

dooms::reflection::eTemplateTypeCategory dooms::reflection::helper::GetTempalteTypeCategory(const DTemplateType& dTemplateType)
{
	const std::string templateTypeName = dTemplateType.GetTemplateTypeName();

	eTemplateTypeCategory templateTypeCategory = eTemplateTypeCategory::NotSupported;

	if(templateTypeName == "std::unique_ptr" || templateTypeName == "std::shared_ptr")
	{
		templateTypeCategory = eTemplateTypeCategory::SmartPointer;
	}
	else if (templateTypeName == "std::vector" || templateTypeName == "std::array")
	{
		templateTypeCategory = eTemplateTypeCategory::RandomAccessIterator;
	}

	return templateTypeCategory;
}

dooms::reflection::DType dooms::reflection::helper::GetStdTemplateElementTypeDType
(
	const DTemplateType& dTemplateType
)
{
	const std::string templateTypeName = dTemplateType.GetTemplateTypeName();
	dooms::reflection::DType dType{};
	if
	( 
		(templateTypeName == "std::vector") ||
		(templateTypeName == "std::array") ||
		(templateTypeName == "std::shared_ptr")||
		(templateTypeName == "std::unique_ptr") 
	)
	{
		const reflection::DTemplateArgumentType templateArgumentType = dTemplateType.GetTemplateArgumentType(0);
		dType = templateArgumentType;
	}

	D_ASSERT(dType.IsValid() == true);

	return dType;
}

bool dooms::reflection::helper::GetStdTemplateElementTypeIsPointer
(
	const DTemplateType& dTemplateType
)
{
	bool isElementTypeIsPointer = false;
	
	const std::string templateTypeName = dTemplateType.GetTemplateTypeName();
	if
	(
		(templateTypeName == "std::vector") ||
		(templateTypeName == "std::array") ||
		(templateTypeName == "std::shared_ptr") ||
		(templateTypeName == "std::unique_ptr")
	)
	{
		isElementTypeIsPointer = dTemplateType.GetTemplateArgumentType(0).GetIsTemplateArgumentPointerType();
	}

	return isElementTypeIsPointer;
}
