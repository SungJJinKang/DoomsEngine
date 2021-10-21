#include "TestComponent2.h"

#include <Game/ConfigData.h>

void doom::TestComponent2::InitComponent()
{
	volatile auto a = doom::ConfigData::GetSingleton()->GetConfigData().GetValue<doom::userinput::eKEY_CODE>("SHORTCUT", "PRINT_THREAD_USAGE");
	
}

void doom::TestComponent2::UpdateComponent()
{
}

void doom::TestComponent2::OnEndOfFrame_Component()
{

}
