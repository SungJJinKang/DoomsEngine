#include "PlainComponent.h"

using namespace doom;

PlainComponent::PlainComponent() : Component() {}

PlainComponent::~PlainComponent()
{
}

void PlainComponent::InitComponent_Internal(Entity& entity)
{
	Component::InitComponent_Internal(entity);
}

void PlainComponent::UpdateComponent_Internal()
{
	Component::UpdateComponent_Internal();
}

void PlainComponent::OnEndOfFrame_Component_Internal()
{
	Component::OnEndOfFrame_Component_Internal();
}

void PlainComponent::OnDestroy_Internal()
{
	Component::OnDestroy_Internal();
}

void PlainComponent::OnActivated_Internal()
{
	Component::OnActivated_Internal();
}

void PlainComponent::OnDeActivated_Internal()
{
	Component::OnDeActivated_Internal();
}

