#include "TestComponent.h"


#include <Game/ConfigData.h>

void dooms::TestComponent::InitComponent()
{
	volatile auto a = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<dooms::userinput::eKEY_CODE>("SHORTCUT", "PRINT_THREAD_USAGE");
	
}

void dooms::TestComponent::UpdateComponent()
{
}

void dooms::TestComponent::OnEndOfFrame_Component()
{

}
