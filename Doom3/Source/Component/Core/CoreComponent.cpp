#include "CoreComponent.h"

using namespace doom;


CoreComponent::CoreComponent() : Component() {}

CoreComponent::~CoreComponent()
{
}

void doom::CoreComponent::InitComponent_Internal(Entity* entity)
{
	Component::InitComponent_Internal(entity);
}

void doom::CoreComponent::UpdateComponent_Internal()
{
	Component::UpdateComponent_Internal();
}

void doom::CoreComponent::OnEndOfFrame_Component_Internal()
{
	Component::OnEndOfFrame_Component_Internal();
}

void doom::CoreComponent::OnDestroy_Internal()
{
	Component::OnDestroy_Internal();
}

void doom::CoreComponent::OnActivated_Internal()
{
	Component::OnActivated_Internal();
}

void doom::CoreComponent::OnDeActivated_Internal()
{
	Component::OnDeActivated_Internal();
}

