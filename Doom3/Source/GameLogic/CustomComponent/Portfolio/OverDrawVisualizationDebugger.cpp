#include "OverDrawVisualizationDebugger.h"

#include <Graphics/graphicsSetting.h>


void dooms::OverDrawVisualizationDebugger::InitComponent()
{
	ShowIsSortObjectFrontToBack();
}

void dooms::OverDrawVisualizationDebugger::ShowIsSortObjectFrontToBack()
{
	if (dooms::graphics::graphicsSetting::IsSortObjectFrontToBack == true)
	{
		D_RELEASE_LOG(eLogType::D_LOG, "Sorting Object Front to Back On");
	}
	else
	{
		D_RELEASE_LOG(eLogType::D_LOG, "Sorting Object Front to Back Off");
	}
}

void dooms::OverDrawVisualizationDebugger::UpdateComponent()
{
	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5))
	{
		dooms::graphics::graphicsSetting::IsSortObjectFrontToBack = !dooms::graphics::graphicsSetting::IsSortObjectFrontToBack;
		ShowIsSortObjectFrontToBack();

	}

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6))
	{
		graphics::graphicsSetting::IsOverDrawVisualizationEnabled = !(graphics::graphicsSetting::IsOverDrawVisualizationEnabled);

	}
}
