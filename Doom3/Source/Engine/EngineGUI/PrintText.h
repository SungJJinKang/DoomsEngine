#pragma once

#include <Core.h>

#include "GUIModules/Modules/LogGUI.h"
#include "EngineGUIServer.h"

namespace dooms
{
	namespace ui
	{
		template<typename... Types>
		extern void PrintText(const char* const format, Types... args)
		{
			if(dooms::ui::EngineGUIServer::GetSingleton()->GetIsEngineGUIAvaliable() == false)
			{
				printf(format, std::forward< Types>(args)...);
				printf("\n");
			}

			if(dooms::ui::LogGUI::GetSingleton() != nullptr)
			{
				dooms::ui::LogGUI::GetSingleton()->LogOnGUI(format, std::forward< Types>(args)...);
			}
		}

	}
}


