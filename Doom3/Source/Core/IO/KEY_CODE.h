#pragma once

#include <Core.h>

#include "SimpleIniParser.h"

#include <Graphics/GraphicsAPI/Input/GraphicsAPIInput.h>

namespace dooms
{
	namespace userinput
	{
		namespace UserInputHelper
		{

			dooms::graphics::GraphicsAPIInput::eKEY_CODE ConvertStringToKeyCode(std::string_view str);

		}
	}
}

template<>
inline dooms::graphics::GraphicsAPIInput::eKEY_CODE IniData::GetValue<dooms::graphics::GraphicsAPIInput::eKEY_CODE>(const std::string& section, const std::string& variableKey) const
{
	auto sectionData = GetSectionData(section, variableKey);

	D_ASSERT(sectionData != nullptr);
	if (sectionData != nullptr)
	{
		return 	dooms::userinput::UserInputHelper::ConvertStringToKeyCode(std::get<std::string>(*sectionData));
	}
	else
	{
		return dooms::graphics::GraphicsAPIInput::eKEY_CODE::ERROR_CODE;
	}
}