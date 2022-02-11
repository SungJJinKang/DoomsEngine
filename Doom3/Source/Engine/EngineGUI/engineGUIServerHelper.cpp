#include "engineGUIServerHelper.h"

#include "GUIModules/Modules/LogGUI.h"
#include "GUIModules/Modules/SceneGUI.h"
#include "GUIModules/Modules/ProfilerGUI.h"
#include "GUIModules/Modules/ThreadProfilerGUI.h"
#include "GUIModules/Modules/MaskedOcclusionCulliingDebugger.h"
#include "GUIModules/Modules/DrawCallCounterGUI.h"

std::vector<dooms::ui::EngineGUIModule*> dooms::ui::engineGUIServerHelper::CreateDefaultEngineGUIModules()
{
	std::vector<dooms::ui::EngineGUIModule*> defaultEngineGUIModules;

	defaultEngineGUIModules.push_back
	(
		dooms::CreateDObject<LogGUI>()
	);

	defaultEngineGUIModules.push_back
	(
		dooms::CreateDObject<SceneGUI>()
	);

	defaultEngineGUIModules.push_back
	(
		dooms::CreateDObject<ProfilerGUI>()
	);

	defaultEngineGUIModules.push_back
	(
		dooms::CreateDObject<ThreadProfilerGUI>()
	);

	/*
	defaultEngineGUIModules.push_back
	(
		dooms::CreateDObject<MaskedOcclusionCulliingDebugger>()
	);
	*/

	defaultEngineGUIModules.push_back
	(
		dooms::CreateDObject<DrawCallCounterGUI>()
	);

	return defaultEngineGUIModules;
}
