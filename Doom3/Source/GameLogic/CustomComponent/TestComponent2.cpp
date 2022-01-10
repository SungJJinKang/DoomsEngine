#include "TestComponent2.h"

#include <Game/ConfigData.h>

void dooms::TestComponent2::InitComponent()
{
	volatile auto a = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<dooms::input::GraphicsAPIInput::eKEY_CODE>("SHORTCUT", "PRINT_THREAD_USAGE");
	
}

void dooms::TestComponent2::UpdateComponent()
{
}

void dooms::TestComponent2::OnEndOfFrame_Component()
{

}
