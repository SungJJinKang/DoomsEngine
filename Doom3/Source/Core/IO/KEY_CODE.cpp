#include "KEY_CODE.h"

#include <Doom_Core.h>

#include "magic_enum.hpp"

dooms::userinput::eKEY_CODE dooms::userinput::UserInputHelper::ConvertStringToKeyCode(std::string_view str)
{
	const auto result = magic_enum::enum_cast<dooms::userinput::eKEY_CODE>(str);

	D_ASSERT(result.has_value() == true);
	if (result.has_value())
	{
		return result.value();
	}
	else
	{
		return dooms::userinput::eKEY_CODE::ERROR_CODE;
	}
}

