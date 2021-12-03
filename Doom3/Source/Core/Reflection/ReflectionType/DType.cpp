#include "DType.h"

#include "../ReflectionManager.h"
#include "DClass.h"
#include "DTemplateType.h"
#include "DEnum.h"

dooms::reflection::DType::DType(const char* const typeFullName)
	:
	dooms::reflection::DPrimitive(dooms::reflection::ReflectionManager::GetSingleton()->GetclcppType(typeFullName)),
	clType(static_cast<const clcpp::Type*>(clPrimitive))
{
	D_ASSERT(clPrimitive != nullptr);
}

dooms::reflection::DClass dooms::reflection::DType::AsDClass() const
{
	D_ASSERT(clType != nullptr);
	D_ASSERT(DPrimitive::IsValid() == true);

	D_ASSERT(GetPrimitiveType() == DPrimitive::ePrimitiveType::CLASS);

	return dooms::reflection::DClass(clType->AsClass());
}

dooms::reflection::DTemplateType dooms::reflection::DType::AsDTemplateType() const
{
	D_ASSERT(clType != nullptr);
	D_ASSERT(DPrimitive::IsValid() == true);

	D_ASSERT(GetPrimitiveType() == DPrimitive::ePrimitiveType::TEMPLATE_TYPE);

	return dooms::reflection::DTemplateType(clType->AsTemplateType());
}

dooms::reflection::DEnum dooms::reflection::DType::AsDEnum() const
{
	D_ASSERT(clType != nullptr);
	D_ASSERT(DPrimitive::IsValid() == true);

	D_ASSERT(GetPrimitiveType() == DPrimitive::ePrimitiveType::ENUM);

	return dooms::reflection::DEnum(clType->AsEnum());
}
