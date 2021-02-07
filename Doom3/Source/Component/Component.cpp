#include "Component.h"
#include "../Core/CoreComponent/Entity.h"

using namespace doom;



constexpr Component::Component() : bIsAddedToEntity{}, mOwnerEntity{}, mTransform{}, mIsActivated{} // Never put parameter to component Constructor (including derived class)
{

}


Component::~Component() // Never put parameter to component Destructor (including derived class)
{

}

constexpr void Component::Init_Internal(Entity& entity)
{
	D_ASSERT(bIsAddedToEntity == false);
	mOwnerEntity = &entity;
	mTransform = entity._Transform();
	bIsAddedToEntity = true;

}

constexpr void Component::Update_Internal()
{

}

constexpr void Component::OnDestroy_Internal()
{

}


constexpr void Component::OnActivated_Internal()
{

}

constexpr void Component::OnDeActivated_Internal()
{

}


