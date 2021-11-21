#include "OverDrawVisualizationDebugger.h"

#include <Graphics/Graphics_Setting.h>
#include <EngineGUI/PrintText.h>

void dooms::OverDrawVisualizationDebugger::InitComponent()
{
	ShowIsSortObjectFrontToBack();
}

void dooms::OverDrawVisualizationDebugger::ShowIsSortObjectFrontToBack()
{
	if (dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack == true)
	{
		dooms::ui::PrintText("Sorting Object Front to Back On");
	}
	else
	{
		dooms::ui::PrintText("Sorting Object Front to Back Off");
	}
}

void dooms::OverDrawVisualizationDebugger::UpdateComponent()
{
	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::userinput::eKEY_CODE::KEY_F5))
	{
		dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = !dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack;
		ShowIsSortObjectFrontToBack();

	}

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::userinput::eKEY_CODE::KEY_F6))
	{
		graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = !(graphics::Graphics_Setting::IsOverDrawVisualizationEnabled);

	}
}
