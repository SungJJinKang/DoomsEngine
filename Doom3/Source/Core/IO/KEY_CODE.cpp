#include "KEY_CODE.h"

#include "magic_enum.hpp"
#include <ConfigurationValue/ConfigurationValue.h>

dooms::input::GraphicsAPIInput::eKEY_CODE dooms::userinput::UserInputHelper::ConvertStringToKeyCode(std::string_view str)
{
	const auto result = magic_enum::enum_cast<dooms::input::GraphicsAPIInput::eKEY_CODE>(str);

	D_ASSERT(result.has_value() == true);
	if (result.has_value())
	{
		return result.value();
	}
	else
	{
		return dooms::input::GraphicsAPIInput::eKEY_CODE::UNKNOWN;
	}
}


template<>
dooms::input::GraphicsAPIInput::eKEY_CODE dooms::IniData::GetValue<dooms::input::GraphicsAPIInput::eKEY_CODE>(const std::string& SectionName, const std::string& KeyName) const
{
	const dooms::GeneralConfigurationValue* const Cvar = GetConfigurationValue(SectionName, KeyName);

	D_ASSERT(Cvar != nullptr);
	if (Cvar != nullptr)
	{
		return 	dooms::userinput::UserInputHelper::ConvertStringToKeyCode(Cvar->AsString());
	}
	else
	{
		return dooms::input::GraphicsAPIInput::eKEY_CODE::UNKNOWN;
	}
}
