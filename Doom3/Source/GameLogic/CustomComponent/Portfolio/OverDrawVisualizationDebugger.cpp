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
		doom::graphics::GraphicsAPIManager::SetWindowTitle("F2 : Sorting Objects Front To Back On/Off ( Current Value : On )");
	}
	else
	{
		doom::ui::PrintText("Sorting Object Front to Back Off");
		doom::graphics::GraphicsAPIManager::SetWindowTitle("F2 : Sorting Objects Front To Back On/Off ( Current Value : Off )");
	}
}

void doom::OverDrawVisualizationDebugger::UpdateComponent()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F2))
	{
		doom::graphics::Graphics_Setting::IsSortObjectFrontToBack = !doom::graphics::Graphics_Setting::IsSortObjectFrontToBack;
		ShowIsSortObjectFrontToBack();

	}
}
