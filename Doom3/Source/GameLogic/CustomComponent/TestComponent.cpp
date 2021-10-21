#include "TestComponent.h"


#include <Game/ConfigData.h>

void doom::TestComponent::InitComponent()
{
	volatile auto a = doom::ConfigData::GetSingleton()->GetConfigData().GetValue<doom::userinput::eKEY_CODE>("SHORTCUT", "PRINT_THREAD_USAGE");
	
}

void doom::TestComponent::UpdateComponent()
{
}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
