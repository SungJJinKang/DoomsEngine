#include "ServerComponent.h"

using namespace dooms;


ServerComponent::ServerComponent() : Component() {}

ServerComponent::~ServerComponent()
{
}


void dooms::ServerComponent::InitComponent_Internal(Entity* entity)
{
	Component::InitComponent_Internal(entity);
}

void dooms::ServerComponent::UpdateComponent_Internal()
{
	Component::UpdateComponent_Internal();
}

void dooms::ServerComponent::FixedUpdateComponent_Internal()
{
	Component::FixedUpdateComponent_Internal();
}

void dooms::ServerComponent::OnEndOfFrame_Component_Internal()
{
	Component::OnEndOfFrame_Component_Internal();
}

void dooms::ServerComponent::OnDestroy_Internal()
{
	Component::OnDestroy_Internal();
}

void dooms::ServerComponent::OnActivated_Internal()
{
	Component::OnActivated_Internal();
}

void dooms::ServerComponent::OnDeActivated_Internal()
{
	Component::OnDeActivated_Internal();
}

