#include "TestComponent.h"


#include <Game/ConfigData.h>

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
