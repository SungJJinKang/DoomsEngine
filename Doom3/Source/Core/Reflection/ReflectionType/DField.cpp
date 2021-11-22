#include "DField.h"

#include "ToString.h"
#include "DAttribute.h"
#include "DAttributeList.h"

void* dooms::reflection::DField::GetRawFieldValue(void* const dObject)
{
	D_ASSERT(clField != nullptr);

	if(clField != nullptr)
	{
		return reinterpret_cast<char*>(dObject) + clField->offset;
	}
	else
	{
		return nullptr;
	}
}

std::string dooms::reflection::DField::ToString(void* const dObject)
{
	return GetStringFromReflectionData(GetFieldTypeHashValue(), GetRawFieldValue(dObject));
}

dooms::reflection::DAttributeList dooms::reflection::DField::GetAttributeList() const
{
	std::vector<dooms::reflection::DAttribute> attributeList;

	D_ASSERT(clField != nullptr);

	attributeList.reserve(clField->attributes.size);
	for(UINT32 i = 0 ; i < clField->attributes.size ; i++)
	{
		attributeList.emplace_back(clField->attributes[i]);
	}

	return std::move(attributeList);
}
