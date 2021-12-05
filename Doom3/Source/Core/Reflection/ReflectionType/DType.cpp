#include "DType.h"

#include "../ReflectionManager.h"
#include "DClass.h"
#include "DTemplateType.h"
#include "DEnum.h"

std::unordered_map<UINT32, bool> dooms::reflection::DType::IsDerivedFromDObjectHashMap{};

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

bool dooms::reflection::DType::GetIsDerivedFromDObject() const
{
	D_ASSERT(clType != nullptr);

	bool isDerivedFromDObject = false;

	const UINT32 typeHashValue = GetPrimitiveHashValue();
	auto iter = IsDerivedFromDObjectHashMap.find(typeHashValue);
	if (iter == IsDerivedFromDObjectHashMap.end())
	{
		isDerivedFromDObject = clType->DerivesFrom(dooms::DObject::TYPE_FULL_NAME_HASH_VALUE);
		IsDerivedFromDObjectHashMap.emplace(typeHashValue, isDerivedFromDObject);
	}
	else
	{
		isDerivedFromDObject = iter->second;
	}

	return isDerivedFromDObject;
}
