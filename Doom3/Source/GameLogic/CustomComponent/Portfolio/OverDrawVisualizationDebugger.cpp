#include "OverDrawVisualizationDebugger.h"

#include <Graphics/Graphics_Setting.h>
#include <UI/PrintText.h>
#include <Graphics/GraphicsAPIManager.h>

void doom::OverDrawVisualizationDebugger::InitComponent()
{
	ShowIsSortObjectFrontToBack();
}

void doom::OverDrawVisualizationDebugger::ShowIsSortObjectFrontToBack()
{
	if (doom::graphics::Graphics_Setting::IsSortObjectFrontToBack == true)
	{
		doom::ui::PrintText("Sorting Object Front to Back On");
	}
	else
	{
		doom::ui::PrintText("Sorting Object Front to Back Off");
	}
}

void doom::OverDrawVisualizationDebugger::UpdateComponent()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F5))
	{
		doom::graphics::Graphics_Setting::IsSortObjectFrontToBack = !doom::graphics::Graphics_Setting::IsSortObjectFrontToBack;
		ShowIsSortObjectFrontToBack();

	}

	if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F6))
	{
		graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = !(graphics::Graphics_Setting::IsOverDrawVisualizationEnabled);

	}
}
