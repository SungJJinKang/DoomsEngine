#include "DField.h"

#include "ToString.h"

std::string dooms::reflection::DField::ToString(void* const dObject)
{
	return GetStringFromReflectionData(GetFieldTypeHashValue(), GetRawFieldValue(dObject));
}
