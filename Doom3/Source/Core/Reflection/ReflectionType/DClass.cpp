#include "DClass.h"

#include "../ReflectionManager.h"

std::unordered_map<UINT32, std::vector<dooms::reflection::DField>> dooms::reflection::DClass::PropertyCacheHashMap{};

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

	void GetDProperties_Recursive(const clcpp::Class* const clcppClass, std::vector<dooms::reflection::DField>& list)
	{
		D_ASSERT(clcppClass != nullptr);

		for (size_t i = 0; i < clcppClass->base_types.size; i++)
		{
			if (clcppClass->base_types[i]->kind == clcpp::Primitive::Kind::KIND_CLASS)
			{
				GetDProperties_Recursive(clcppClass->base_types[i]->AsClass(), list);
			}
		}

		for (std::ptrdiff_t i = clcppClass->fields.size ; i > 0 ; i--)
		{
			list.emplace_back(clcppClass->fields[i - 1]);
		}

		
		
	}

	// Return DProperties of passed clcpp::Class
	std::vector<dooms::reflection::DField> GetDProperties(const clcpp::Class* const clcppClass)
	{
		D_ASSERT(clcppClass != nullptr);

		const clcpp::Class* targetclcppClasss = clcppClass;

		std::vector<dooms::reflection::DField> dProperty{};

		GetDProperties_Recursive(clcppClass, dProperty);

		// iterate base class
		return dProperty;
	}
}

dooms::reflection::DClass::DClass(dooms::DObject* const dObject)
	: DClass(dObject->GetTypeHashVlue())
{
}

dooms::reflection::DClass::DClass(const UINT32 nameHash)
	: DType(dClassHelper::GetclcppClass(nameHash)), clClass(clType->AsClass())
{
	D_ASSERT(clPrimitive != nullptr);

}

dooms::reflection::DClass::DClass(const clcpp::Class* const clcppType)
	: DType(clcppType), clClass(clcppType)
{
	D_ASSERT(clPrimitive != nullptr);
}


const std::vector<dooms::reflection::DField>& dooms::reflection::DClass::GetFieldList() const
{
	std::vector<dooms::reflection::DField>* propertyList = nullptr;

	auto iter = PropertyCacheHashMap.find(clPrimitive->name.hash);
	if(iter == PropertyCacheHashMap.end())
	{
		std::vector<dooms::reflection::DField> cachedPropertyList = dClassHelper::GetDProperties(clClass);
		auto result = PropertyCacheHashMap.emplace(clPrimitive->name.hash, std::move(cachedPropertyList));
		propertyList = &(result.first->second);
	}
	else
	{
		propertyList = &(iter->second);
	}

	D_ASSERT(propertyList != nullptr);

	return *propertyList;
}

bool dooms::reflection::DClass::GetField(const char* const fieldName, dooms::reflection::DField& dProperty) const
{
	const std::vector<dooms::reflection::DField>& propertyList = GetFieldList();

	bool isSuccess = false;
	
	for(size_t i = 0 ; i < propertyList.size() ; i++)
	{
		if(std::strcmp(propertyList[i].GetFieldVariableFullName(), fieldName) == 0)
		{// field's name is short name
			dProperty = propertyList[i];
			isSuccess = true;
			break;
		}
		//propertyList[i].get
	}

	D_ASSERT_LOG(isSuccess == true, "Fail to find Field ( %s ) from ( %s )", fieldName, GetTypeFullName());

	return isSuccess;
}
