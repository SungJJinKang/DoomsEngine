#include "DType.h"

#include "../ReflectionManager.h"
dooms::reflection::DType::DType(const char* const typeFullName)
	:
	dooms::reflection::DPrimitive(dooms::reflection::ReflectionManager::GetSingleton()->GetclcppType(typeFullName)),
	clType(static_cast<const clcpp::Type*>(clPrimitive))
{
	D_ASSERT(clPrimitive != nullptr);
}
