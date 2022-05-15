#include "ConfigurationValue.h"

void dooms::ConfigurationValueManager::AddGeneralConfigurationValueToList(GeneralConfigurationValue* const Value)
{
	bool bIsAddToList = true;

	{
		if(Value == nullptr)
		{
			D_ASSERT_LOG
			(
				false,
				"Fail to AddGeneralConfigurationValueToList ( Passed Value is Empty )"
			);
		}
	}

	{
		auto Iter = GeneralConfigurationValueList.Data.find(Value->GetValueCategory());
		if (Iter != GeneralConfigurationValueList.Data.end())
		{
			if(Iter->second.find(Value->GetValueName()) != Iter->second.end())
			{
				bIsAddToList = false;
				D_ASSERT_LOG
				(
					false,
					"Fail to AddGeneralConfigurationValueToList ( %s - %s Already Exist )",
					Value->GetValueCategory(),
					Value->GetValueName()
				);
			}
		}
	}
	

	if(bIsAddToList == true)
	{
		if(GeneralConfigurationValueList.Data.find(Value->GetValueCategory()) == GeneralConfigurationValueList.Data.end())
		{
			GeneralConfigurationValueList.Data.insert({Value->GetValueCategory(), std::unordered_map<std::string, GeneralConfigurationValue*>{}});
		}

		GeneralConfigurationValueList.Data[Value->GetValueCategory()].insert_or_assign(Value->GetValueName(), Value);
	}
}

const char* dooms::GeneralConfigurationValue::GetValueCategory() const
{
	return mCategory;
}

const char* dooms::GeneralConfigurationValue::GetValueName() const
{
	return mName;
}

const char* dooms::GeneralConfigurationValue::GetValueDescription() const
{
	return mDescription;
}

dooms::ConfigurationValueContainer& dooms::ConfigurationValueManager::GetGeneralConfigurationValueList()
{
	return GeneralConfigurationValueList;
}

const dooms::ConfigurationValueContainer& dooms::ConfigurationValueManager::GetGeneralConfigurationValueList() const
{
	return GeneralConfigurationValueList;
}

dooms::GeneralConfigurationValue* dooms::ConfigurationValueManager::GetGeneralConfigurationValue
(

	const char* const Category, const char* const Name
)
{
	return const_cast<dooms::GeneralConfigurationValue*>(static_cast<const dooms::ConfigurationValueManager*>(this)->GetGeneralConfigurationValue(Category, Name));
}

const dooms::GeneralConfigurationValue* dooms::ConfigurationValueManager::GetGeneralConfigurationValue
(

	const char* const Category, const char* const Name
) const
{
	const dooms::GeneralConfigurationValue* GeneralConfigurationValue = nullptr;

	auto CategoryIter = GeneralConfigurationValueList.Data.find(Category);
	if (CategoryIter != GeneralConfigurationValueList.Data.end())
	{
		auto ValueIter = CategoryIter->second.find(Name);
		if (ValueIter != CategoryIter->second.end())
		{
			GeneralConfigurationValue = ValueIter->second;
		}
	}

	return GeneralConfigurationValue;
}


