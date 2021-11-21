#include "DPrimitive.h"

#include <string_view>

#include "Reflection/ReflectionManager.h"

const char* dPrimitiveHelper::GetShortNamePointer(const char* const name)
{
	D_ASSERT(name != nullptr);

	const std::string_view nameStringView = name;
	const size_t lastTypeDivider = nameStringView.find_last_of("::");

	if (lastTypeDivider != std::string::npos)
	{
		return name + lastTypeDivider + 1;
	}
	else
	{
		return name;
	}
}

dooms::reflection::DPrimitive::DPrimitive()
	: clPrimitive(nullptr)
{
	D_ASSERT(dooms::reflection::ReflectionManager::GetSingleton() != nullptr);
	D_ASSERT(dooms::reflection::ReflectionManager::GetSingleton()->GetIsReflectionDatabaseLoaded() == true);
}


dooms::reflection::DPrimitive::DPrimitive(const clcpp::Primitive* const _clPrimitive)
	: clPrimitive(_clPrimitive)
{
	D_ASSERT(dooms::reflection::ReflectionManager::GetSingleton() != nullptr);
	D_ASSERT(dooms::reflection::ReflectionManager::GetSingleton()->GetIsReflectionDatabaseLoaded() == true);
}

