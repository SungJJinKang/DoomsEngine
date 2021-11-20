#include "DEnum.h"

#include "Reflection/ReflectionManager.h"

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


dooms::reflection::DEnum::DEnum(const UINT32 nameHash)
	: DType(dClassHelper::GetclcppEnum(nameHash)), clEnum(clType->AsEnum())
{
	D_ASSERT(clEnum != nullptr);
}

const char* dooms::reflection::DEnum::GetNameOfEnumConstantsValue
(
	const INT32 value,
	const dooms::reflection::ePrimitiveNameType primitiveNameType
) const
{
	const char* valueName = nullptr;

	if (primitiveNameType == dooms::reflection::ePrimitiveNameType::Full)
	{
		valueName = clEnum->GetValueName(value);
	}
	else if (primitiveNameType == dooms::reflection::ePrimitiveNameType::Short)
	{
		valueName = dPrimitiveHelper::GetShortNamePointer(clEnum->GetValueName(value));
	}

	return valueName;
}

const bool dooms::reflection::DEnum::GetValue(const char* const valueName, INT32& result) const
{
	bool isSuccess = false;

	const std::string enumConstantFullName = std::string(GetPrimitiveFullName()) + "::" + valueName;

	// TODO : Optimization

	for(UINT32 i = 0 ; i < clEnum->constants.size ; i++)
	{
		if(std::strcmp(clEnum->constants[i]->name.text, enumConstantFullName.data()) == 0)
		{
			result = clEnum->constants[i]->value;
			isSuccess = true;
			break;
		}
	}

	return isSuccess;
}
