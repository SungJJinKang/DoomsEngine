#include "ServerComponent.h"

using namespace doom;


ServerComponent::ServerComponent() : Component() {}



void doom::ServerComponent::InitComponent_Internal(Entity* entity)
{
	Component::InitComponent_Internal(entity);
}

void doom::ServerComponent::UpdateComponent_Internal()
{
	Component::UpdateComponent_Internal();
}

void doom::ServerComponent::FixedUpdateComponent_Internal()
{
	Component::FixedUpdateComponent_Internal();
}

void doom::ServerComponent::OnEndOfFrame_Component_Internal()
{
	Component::OnEndOfFrame_Component_Internal();
}

void doom::ServerComponent::OnDestroy_Internal()
{
	Component::OnDestroy_Internal();
}

void doom::ServerComponent::OnActivated_Internal()
{
	Component::OnActivated_Internal();
}

void doom::ServerComponent::OnDeActivated_Internal()
{
	Component::OnDeActivated_Internal();
}

