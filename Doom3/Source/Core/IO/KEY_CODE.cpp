#include "KEY_CODE.h"

#include <Doom_Core.h>

#include "magic_enum.hpp"

doom::userinput::eKEY_CODE doom::userinput::UserInputHelper::ConvertStringToKeyCode(std::string_view str)
{
	const auto result = magic_enum::enum_cast<doom::userinput::eKEY_CODE>(str);

	D_ASSERT(result.has_value() == true);
	if (result.has_value())
	{
		return result.value();
	}
	else
	{
		return doom::userinput::eKEY_CODE::ERROR_CODE;
	}
}

