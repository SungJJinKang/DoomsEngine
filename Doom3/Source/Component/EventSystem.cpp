#include "EventSystem.h"

void dooms::EventSystem::InitComponent()
{
	PlainComponent::InitComponent();
}

void dooms::EventSystem::FixedUpdateComponent()
{
	PlainComponent::FixedUpdateComponent();
}

void dooms::EventSystem::UpdateComponent()
{
	PlainComponent::UpdateComponent();
}

void dooms::EventSystem::OnEndOfFrame_Component()
{
	PlainComponent::OnEndOfFrame_Component();
}

dooms::EventSystem::~EventSystem()
{
}
