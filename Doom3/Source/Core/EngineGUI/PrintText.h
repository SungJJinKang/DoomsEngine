#pragma once

#include <Core.h>

#include "GUIModules/LogGUI.h"

namespace dooms
{
	namespace ui
	{
		template<typename... Types>
		extern void PrintText(const char* const format, Types... args)
		{
			dooms::ui::log::LogOnGUI(format, std::forward< Types>(args)...);
		}

	}
}


