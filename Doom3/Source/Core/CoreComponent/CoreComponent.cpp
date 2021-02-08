#include "CoreComponent.h"

using namespace doom;


CoreComponent::CoreComponent() : Component() {}

CoreComponent::~CoreComponent()
{
}

void CoreComponent::Init_Internal(Entity& entity)
{
	Component::Init_Internal(entity);
}
