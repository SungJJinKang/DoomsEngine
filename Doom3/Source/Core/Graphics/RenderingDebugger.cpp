#include "RenderingDebugger.h"

#include "Graphics_Setting.h"
#include <UI/PrintText.h>
#include "IO/UserInput_Server.h"

void doom::graphics::RenderingDebugger::UpdateDebugger()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F5))
	{
		RenderingDebugger::PrintDrawCallCounter();
	}
}

void doom::graphics::RenderingDebugger::PrintDrawCallCounter()
{
	doom::ui::PrintText("Draw Call : %d", RenderingDebugger::DrawCallCounter);
}
