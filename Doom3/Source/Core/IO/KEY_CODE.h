#pragma once

#include <Core.h>

#include <Misc/IniFile/SimpleIniParser.h>

#include <Graphics/GraphicsAPI/Input/GraphicsAPIInput.h>

namespace dooms
{
	namespace userinput
	{
		namespace UserInputHelper
		{

			dooms::input::GraphicsAPIInput::eKEY_CODE ConvertStringToKeyCode(std::string_view str);

		}
	}
}

template<>
dooms::input::GraphicsAPIInput::eKEY_CODE dooms::IniData::GetValue<dooms::input::GraphicsAPIInput::eKEY_CODE>(const std::string& SectionName, const std::string& KeyName) const;