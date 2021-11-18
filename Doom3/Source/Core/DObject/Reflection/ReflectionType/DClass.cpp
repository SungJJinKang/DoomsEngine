#include "DClass.h"

#include "../ReflectionManager.h"

#include <unordered_map>

namespace dClassHelper
{
	const clcpp::Class* GetclcppClass(const UINT32 nameHash)
	{
		const clcpp::Database& db = dooms::reflection::ReflectionManager::GetSingleton()->GetclcppDatabase();
		const clcpp::Type* const clcppType = db.GetType(nameHash);
		D_ASSERT(clcppType != nullptr);
		D_ASSERT(clcppType->kind == clcpp::Primitive::KIND_CLASS);
		return clcppType->AsClass();
	}

	void GetDProperties_Recursive(const clcpp::Class* const clcppClass, std::vector<dooms::DProperty>& list)
	{
		D_ASSERT(clcppClass != nullptr);

		for (size_t i = 0; i < clcppClass->base_types.size; i++)
		{
			if (clcppClass->base_types[i]->kind == clcpp::Primitive::Kind::KIND_CLASS)
			{
				GetDProperties_Recursive(clcppClass->base_types[i]->AsClass(), list);
			}
		}

		for (size_t i = 0; i < clcppClass->fields.size; i++)
		{
			list.emplace_back(clcppClass->fields[i]);
		}

		
		
	}

	// Return DProperties of passed clcpp::Class
	std::vector<dooms::DProperty> GetDProperties(const clcpp::Class* const clcppClass)
	{
		D_ASSERT(clcppClass != nullptr);

		const clcpp::Class* targetclcppClasss = clcppClass;

		std::vector<dooms::DProperty> dProperty{};

		GetDProperties_Recursive(clcppClass, dProperty);

		// iterate base class
		return dProperty;
	}
}

dooms::DClass::DClass(dooms::DObject* const dObject)
	: DClass(dObject->GetTypeHashVlue())
{
}

dooms::DClass::DClass(const UINT32 nameHash)
	: DType(dClassHelper::GetclcppClass(nameHash)), clClass(clType->AsClass())
{
	D_ASSERT(clPrimitive != nullptr);

}

dooms::DClass::DClass(const clcpp::Class* const clcppType)
	: DType(clcppType), clClass(clcppType)
{
	D_ASSERT(clPrimitive != nullptr);
}


const std::vector<dooms::DProperty> dooms::DClass::GetPropertyList() const
{
	static std::unordered_map<UINT32, std::vector<dooms::DProperty>> PropertyCacheHashMap;

	std::vector<dooms::DProperty> propertyList;

	auto iter = PropertyCacheHashMap.find(clPrimitive->name.hash);
	if(iter == PropertyCacheHashMap.end())
	{
		propertyList = dClassHelper::GetDProperties(clClass);
		PropertyCacheHashMap.emplace(clPrimitive->name.hash, propertyList);
	}
	else
	{
		propertyList = iter->second;
	}

	return propertyList;
}
