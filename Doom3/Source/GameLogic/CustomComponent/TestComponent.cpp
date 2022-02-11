#include "TestComponent.h"


#include <EngineConfigurationData/ConfigData.h>

void dooms::TestComponent::InitComponent()
{
	mGCTestDObject = dooms::CreateDObject<GCTestDObject>();
}

void dooms::TestComponent::UpdateComponent()
{
}

void dooms::TestComponent::OnEndOfFrame_Component()
{

}
