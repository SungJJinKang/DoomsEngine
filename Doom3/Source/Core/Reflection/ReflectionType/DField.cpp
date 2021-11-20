#include "DField.h"

#include "ToString.h"

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
