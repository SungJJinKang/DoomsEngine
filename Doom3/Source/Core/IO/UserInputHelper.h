#pragma once

#include <string>

#include "KEY_CODE.h"

namespace doom
{
	namespace userinput
	{
		namespace UserInputHelper
		{

			doom::userinput::eKEY_CODE ConvertStringToKeyCode(std::string_view str);

		}
	}
}

