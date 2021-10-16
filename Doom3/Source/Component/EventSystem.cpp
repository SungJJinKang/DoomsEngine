#include "EventSystem.h"

void doom::EventSystem::InitComponent()
{
	PlainComponent::InitComponent();
}

void doom::EventSystem::FixedUpdateComponent()
{
	PlainComponent::FixedUpdateComponent();
}

void doom::EventSystem::UpdateComponent()
{
	PlainComponent::UpdateComponent();
}

void doom::EventSystem::OnEndOfFrame_Component()
{
	PlainComponent::OnEndOfFrame_Component();
}

doom::EventSystem::~EventSystem()
{
}
