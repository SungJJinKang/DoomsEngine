#include "SimpleIniParser.h"

#include <ConfigurationValue/ConfigurationValue.h>

template <>
bool dooms::IniData::GetValue<bool>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	if (Cvar != nullptr)
	{
		return Cvar->AsBoolean();
	}
	else
	{
		D_ASSERT_LOG(false, "The config value doesn't exist ( Section : %s, Key : %s )", SectionName.c_str(), KeyName.c_str());
		return bool{};
	}
}

template <>
INT32 dooms::IniData::GetValue<INT32>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	if (Cvar != nullptr)
	{
		return Cvar->AsInt32();
	}
	else
	{
		D_ASSERT_LOG(false, "The config value doesn't exist ( Section : %s, Key : %s )", SectionName.c_str(), KeyName.c_str());
		return INT32{};
	}
}

template <>
INT64 dooms::IniData::GetValue<INT64>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	if (Cvar != nullptr)
	{
		return Cvar->AsInt64();
	}
	else
	{
		D_ASSERT_LOG(false, "The config value doesn't exist ( Section : %s, Key : %s )", SectionName.c_str(), KeyName.c_str());
		return INT64{};
	}
}

template <>
FLOAT32 dooms::IniData::GetValue<FLOAT32>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	if (Cvar != nullptr)
	{
		return Cvar->AsFloat32();
	}
	else
	{
		D_ASSERT_LOG(false, "The config value doesn't exist ( Section : %s, Key : %s )", SectionName.c_str(), KeyName.c_str());
		return FLOAT32{};
	}
}

template <>
FLOAT64 dooms::IniData::GetValue<FLOAT64>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	if (Cvar != nullptr)
	{
		return Cvar->AsFloat64();
	}
	else
	{
		D_ASSERT_LOG(false, "The config value doesn't exist ( Section : %s, Key : %s )", SectionName.c_str(), KeyName.c_str());
		return FLOAT64{};
	}
}

template <>
std::string dooms::IniData::GetValue<std::string>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	if (Cvar != nullptr)
	{
		return Cvar->AsString();
	}
	else
	{
		D_ASSERT_LOG(false, "The config value doesn't exist ( Section : %s, Key : %s )", SectionName.c_str(), KeyName.c_str());
		return std::string{};
	}
}

dooms::GeneralConfigurationValue* dooms::IniData::GetConfigurationValue
(
	const std::string& SectionName,
	const std::string& KeyName
) const
{
	return ConfigurationValueManager::GetConfigurationValueManager()->GetGeneralConfigurationValue(SectionName.c_str(), KeyName.c_str());
}
