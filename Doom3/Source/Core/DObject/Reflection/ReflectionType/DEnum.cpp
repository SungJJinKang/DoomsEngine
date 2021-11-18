#include "DEnum.h"

#include <string_view>

#include "DObject/Reflection/ReflectionManager.h"

namespace dClassHelper
{
	const clcpp::Enum* GetclcppEnum(const UINT32 nameHash)
	{
		const clcpp::Database& db = dooms::reflection::ReflectionManager::GetSingleton()->GetclcppDatabase();
		const clcpp::Type* const clcppType = db.GetType(nameHash);
		D_ASSERT(clcppType != nullptr);
		D_ASSERT(clcppType->kind == clcpp::Primitive::KIND_ENUM);
		return clcppType->AsEnum();
	}
}

const char* dooms::dEnumHelper::GetShortNamePointer(const char* const name)
{
	const std::string_view nameStringView = name;
	const size_t lastTypeDivider = nameStringView.find_last_of("::");

	if(lastTypeDivider != std::string::npos)
	{
		return name + lastTypeDivider;
	}
	else
	{
		return name;
	}
}

dooms::DEnum::DEnum(const UINT32 nameHash)
	: DType(dClassHelper::GetclcppEnum(nameHash)), clEnum(clType->AsEnum())
{
	D_ASSERT(clPrimitive != nullptr);
}

const bool dooms::DEnum::GetValue(const char* const valueName, INT32& result)
{
	bool isSuccess = false;

	for(UINT32 i = 0 ; i < clEnum->constants.size ; i++)
	{
		if(std::strcmp(dEnumHelper::GetShortNamePointer(clEnum->constants[i]->name.text), valueName) == 0)
		{
			result = clEnum->constants[i]->value;
			isSuccess = true;
			break;
		}
	}

	return isSuccess;
}
