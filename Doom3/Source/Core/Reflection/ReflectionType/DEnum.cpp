#include "DEnum.h"

#include <vector>

#include "../Reflection.h"
#include "Reflection/ReflectionManager.h"
#include "DAttributeList.h"

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

dooms::reflection::DEnum::DEnum(const char* const typeFullName)
	: DEnum(dooms::reflection::ReflectionManager::GetSingleton()->GetclcppNameHash(typeFullName))
{
}

const char* dooms::reflection::DEnum::GetNameOfEnumConstantValue
(
	const INT32 value,
	const dooms::reflection::ePrimitiveNameType primitiveNameType
) const
{
	D_ASSERT(clEnum != nullptr);

	const char* valueName = nullptr;

	if (primitiveNameType == dooms::reflection::ePrimitiveNameType::Full)
	{
		valueName = clEnum->GetValueName(value);
	}
	else if (primitiveNameType == dooms::reflection::ePrimitiveNameType::Short)
	{
		valueName = dPrimitiveHelper::GetShortNamePointer(clEnum->GetValueName(value));
	}

	D_ASSERT(valueName != 0);

	return valueName;
}

const char* dooms::reflection::DEnum::GetNameOfEnumConstantIndex
(
	const INT32 index,
	const dooms::reflection::ePrimitiveNameType primitiveNameType
) const
{
	D_ASSERT(clEnum != nullptr);
	D_ASSERT(index >= 0 && index < static_cast<INT32>(clEnum->constants.size));

	const char* valueName = nullptr;

	if (primitiveNameType == dooms::reflection::ePrimitiveNameType::Full)
	{
		valueName = clEnum->constants[index]->name.text;
	}
	else if (primitiveNameType == dooms::reflection::ePrimitiveNameType::Short)
	{
		valueName = dPrimitiveHelper::GetShortNamePointer(clEnum->constants[index]->name.text);
	}

	D_ASSERT(valueName != 0);

	return valueName;
}

const bool dooms::reflection::DEnum::GetEnumConstantValue(const char* const valueName, INT32& result) const
{
	D_ASSERT(clEnum != nullptr);

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

const bool dooms::reflection::DEnum::GetEnumConstantValue(const INT32 index, INT32& result) const
{
	D_ASSERT(clEnum != nullptr);
	D_ASSERT(index >= 0 && index < static_cast<INT32>(clEnum->constants.size));

	bool isSuccess = false;

	if(index >= 0 && index < static_cast<INT32>(clEnum->constants.size))
	{
		result = clEnum->constants[index]->value;
		isSuccess = true;
	}
	
	return isSuccess;
}

size_t dooms::reflection::DEnum::GetEnumConstantIndex(const char* const enumConstantName) const
{
	size_t enumConstantIndex = -1;

	for (UINT32 i = 0; i < clEnum->constants.size; i++)
	{
		if (std::strcmp(clEnum->constants[i]->name.text, enumConstantName) == 0)
		{
			enumConstantIndex = i;
			break;
		}
	}

	return enumConstantIndex;
}

size_t dooms::reflection::DEnum::GetEnumConstantIndex(const INT32 value) const
{
	size_t enumConstantIndex = -1;

	for (UINT32 i = 0; i < clEnum->constants.size; i++)
	{
		if (clEnum->constants[i]->value == value)
		{
			enumConstantIndex = i;
			break;
		}
	}

	return enumConstantIndex;
}

size_t dooms::reflection::DEnum::GetEnumConstantsCount() const
{
	D_ASSERT(clEnum != nullptr);

	return clEnum->constants.size;
}


dooms::reflection::DAttributeList dooms::reflection::DEnum::GetDAttributeList() const
{
	std::vector<dooms::reflection::DAttribute> attributeList;

	D_ASSERT(clEnum != nullptr);

	attributeList.reserve(clEnum->attributes.size);
	for (UINT32 i = 0; i < clEnum->attributes.size; i++)
	{
		attributeList.emplace_back(clEnum->attributes[i]);
	}

	return std::move(attributeList);
}
