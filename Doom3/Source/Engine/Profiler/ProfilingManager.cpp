#include "ProfilingManager.h"

#include <EngineGUI/GUIModules/Modules/ProfilerGUI.h>

void dooms::profiling::profilingManager::AddProfilingData(const char* const tag, const float time)
{
	if(IsValid(dooms::ui::ProfilerGUI::GetSingleton()))
	{
		dooms::ui::ProfilerGUI::GetSingleton()->AddProfilingData(tag, time);
	}	
}
