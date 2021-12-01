#pragma once

#include <Core.h>

#include "GUIModules/LogGUI.h"
#include "engineGUIServer.h"

namespace dooms
{
	namespace ui
	{
		template<typename... Types>
		extern void PrintText(const char* const format, Types... args)
		{
			if(engineGUIServer::GetIsEngineGUIAvaliable() == false)
			{
				printf(format, std::forward< Types>(args)...);
				printf("\n");
			}
			
			dooms::ui::log::LogOnGUI(format, std::forward< Types>(args)...);
		}

	}
}


