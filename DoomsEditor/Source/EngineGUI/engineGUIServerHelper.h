#pragma once

#include <vector>

namespace dooms
{
	namespace ui
	{
		class EngineGUIModule;
		namespace engineGUIServerHelper
		{
			std::vector<EngineGUIModule*> CreateDefaultEngineGUIModules();
		}
	}
}

