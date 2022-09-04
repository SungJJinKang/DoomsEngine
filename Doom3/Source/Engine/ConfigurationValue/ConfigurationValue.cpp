#include "ConfigurationValue.h"


dooms::GeneralConfigurationValue::GeneralConfigurationValue
(
	const std::string& Category,
	const std::string& Name,
	const std::string& Description
)
	: mCategory(Category), mName(Name), mDescription(Description)
{
	ConfigurationValueManager::GetConfigurationValueManager()->RegisterConsoleVariable(this);
}

dooms::ConfigurationValueManager* dooms::ConfigurationValueManager::GetConfigurationValueManager()
{
	static std::unique_ptr<ConfigurationValueManager> StaticConfigurationValueManager = std::make_unique<ConfigurationValueManager>();
	return StaticConfigurationValueManager.get();
}

void dooms::ConfigurationValueManager::RegisterConsoleVariable(GeneralConfigurationValue* const Value)
{
	if (Value == nullptr)
	{
		D_ASSERT_LOG
		(
			false,
			"Fail to AddGeneralConfigurationValueToList ( Passed Value is Empty )"
		);
	}
	else
	{
		auto CategoryIter = GeneralConfigurationValueList.Data.find(Value->GetValueCategory());

		if (CategoryIter == GeneralConfigurationValueList.Data.end())
		{
			CategoryIter = GeneralConfigurationValueList.Data.insert({ Value->GetValueCategory(), std::unordered_map<std::string, GeneralConfigurationValue*>{} }).first;
		}

		if (CategoryIter->second.find(Value->GetValueName()) != CategoryIter->second.end())
		{
			D_ASSERT_LOG
			(
				false,
				"Fail to AddGeneralConfigurationValueToList ( %s - %s Already Exist )",
				Value->GetValueCategory().c_str(),
				Value->GetValueName().c_str()
			);
		}
		else
		{
			CategoryIter->second.emplace(Value->GetValueName(), Value);
		}
	}
}

const std::string& dooms::GeneralConfigurationValue::GetValueCategory() const
{
	return mCategory;
}

const std::string& dooms::GeneralConfigurationValue::GetValueName() const
{
	return mName;
}

const std::string& dooms::GeneralConfigurationValue::GetValueDescription() const
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

	D_ASSERT_LOG(GeneralConfigurationValue != nullptr, "Console Variable doesn't exist ( Category : %s, ValueNaem : %s )", Category, Name);

	return GeneralConfigurationValue;
}