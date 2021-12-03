#include "DTemplateType.h"

#include <string_view>

#include "DTemplateArgumentType.h"

bool dooms::reflection::dTemplateTypeHelper::GetTemplateTypeNameFromTypeFullName(const char* const typeFullName, std::string& outString)
{
	bool isSuccess = false;

	const size_t templateLeftBrancketsPos = std::string_view(typeFullName).find_first_of('<');

	D_ASSERT(templateLeftBrancketsPos != std::string::npos);
	if(templateLeftBrancketsPos != std::string::npos)
	{
		outString = std::string(typeFullName, templateLeftBrancketsPos);
		isSuccess = true;
	}
	
	return isSuccess;
}

dooms::reflection::DTemplateType::DTemplateType(const clcpp::TemplateType* const _clTemplateType)
	: DType(_clTemplateType), clTemplateType(_clTemplateType)
{
}

size_t dooms::reflection::DTemplateType::GetTemplateArgumentCount() const
{
	D_ASSERT(clTemplateType != nullptr);
	if (clTemplateType != nullptr)
	{
		for (size_t i = 0; i < clcpp::TemplateType::MAX_NB_ARGS; i++)
		{
			if (clTemplateType->parameter_types[i] == nullptr)
			{
				return i;
			}
		}

		return clcpp::TemplateType::MAX_NB_ARGS;
	}
	else
	{
		return 0;
	}
}

dooms::reflection::DTemplateArgumentType dooms::reflection::DTemplateType::GetTemplateArgumentType(const size_t index) const
{
	D_ASSERT(clTemplateType != nullptr);
	D_ASSERT(GetTemplateArgumentCount() > index);

	return dooms::reflection::DTemplateArgumentType(clTemplateType->parameter_types[index], clTemplateType->parameter_ptrs[index]);
}

const std::vector<dooms::reflection::DTemplateArgumentType> dooms::reflection::DTemplateType::GetTemplateArgumentTypes() const
{
	D_ASSERT(clTemplateType != nullptr);

	std::vector<dooms::reflection::DTemplateArgumentType> templateArgumentTypes;

	const size_t templateArgumentCount = GetTemplateArgumentCount();
	templateArgumentTypes.reserve(templateArgumentCount);

	for (size_t i = 0; i < templateArgumentCount; i++)
	{
		templateArgumentTypes.emplace_back(clTemplateType->parameter_types[i], clTemplateType->parameter_ptrs[i]);
	}

	return templateArgumentTypes;
}

std::string dooms::reflection::DTemplateType::GetTemplateTypeName() const
{
	std::string templateTypeName{};
	const bool isSuccess = dTemplateTypeHelper::GetTemplateTypeNameFromTypeFullName(clTemplateType->name.text, templateTypeName);
	D_ASSERT(isSuccess == true);

	return templateTypeName;
}

