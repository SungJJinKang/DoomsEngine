#include "ProfilingManager.h"

#include <EngineGUI/GUIModules/ProfilerGUI.h>

void dooms::profiling::profilingManager::AddProfilingData(const char* const tag, const float time)
{
	dooms::ui::profilerGUI::AddProfilingData(tag, time);
}
