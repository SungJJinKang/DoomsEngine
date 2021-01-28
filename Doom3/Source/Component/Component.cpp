#include "Component.h"
#include "../Core/CoreComponent/Entity.h"

using namespace doom;



Component::Component() : bIsAddedToEntity{}, mOwnerEntity{}, mTransform{}, mIsActivated{} // Never put parameter to component Constructor (including derived class)
{

}


Component::~Component() // Never put parameter to component Destructor (including derived class)
{

}

void Component::OnComponentAttached_Internal(Entity& entity)
{
	D_ASSERT(bIsAddedToEntity == false);
	mOwnerEntity = &entity;
	mTransform = &(entity._Transform());
	bIsAddedToEntity = true;

}

void Component::OnComponentDestroyed_Internal()
{

}


void Component::OnComponentActivated_Internal()
{

}

void Component::OnComponentDeActivated_Internal()
{

}

void Component::OnUpdateComponent_Internal()
{

}

