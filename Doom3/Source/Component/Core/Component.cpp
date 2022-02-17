#include "Component.h"
#include <Scene/Entity.h>
#include "../Transform.h"

using namespace dooms;


void Component::OnSetPendingKill()
{
	Base::OnSetPendingKill();

	OnDestroy_Internal();
	OnDestroy();
	OnDestroyLate();
}

Component::Component() : bIsAddedToEntity{false}, mOwnerEntity{nullptr}, mTransform{nullptr}, IsComponentEnabled{true}
{
	UpdateComponentEnabled();
}

Component::~Component()
{
}

Component::Component(const Component&)
	: bIsAddedToEntity{ false }, mOwnerEntity{ nullptr }, mTransform{nullptr}, IsComponentEnabled{ true }
{
	UpdateComponentEnabled();
}

Component& Component::operator=(const Component&)
{
	bIsAddedToEntity = false;
	mOwnerEntity = nullptr;
	mTransform = nullptr;
	IsComponentEnabled = true;
	UpdateComponentEnabled();
	
	return *this;
}

void dooms::Component::UpdateComponentEnabled()
{
	if(IsComponentEnabled == true)
	{
		OnActivated_Internal();
		OnActivated();
	}
	else
	{
		OnDeActivated_Internal();
		OnDeActivated();
	}
}

void Component::AddLocalDirtyToTransformDirtyReceiver(DirtyReceiver& localDirty)
{
	GetTransform()->mDirtySender.AddDirtyReceiver(&localDirty);
}

void dooms::Component::InitComponent_Internal(Entity* entity)
{
	D_ASSERT(IsValid(entity) == true);

	ChangeDObjectName(GetTypeFullName());
	mOwnerEntity = entity;
	mTransform = entity->GetTransform();
	bIsAddedToEntity = true;
}

void dooms::Component::UpdateComponent_Internal()
{
}


void Component::FixedUpdateComponent_Internal()
{

}

void dooms::Component::OnEndOfFrame_Component_Internal()
{
	FrameDirtyChecker_EndOfFrame();
}

void dooms::Component::OnDestroy_Internal()
{
	if (IsChildOf<Transform>() == false)
	{
		mOwnerEntity->RemoveComponent(this);
	}
	
}

void Component::OnDestroyLate()
{
	SetComponentEnabled(false);
}

void dooms::Component::OnActivated_Internal()
{
	SetDirtyTrueAtThisFrame();
}

void dooms::Component::OnDeActivated_Internal()
{
}

UINT32 Component::GetOwnerEntityLayerIndex() const
{
	return GetOwnerEntity()->GetLayerIndex();
}

void Component::SetComponentEnabled(const bool isEnabled)
{
	IsComponentEnabled = isEnabled;
	UpdateComponentEnabled();
}

void Component::DestroyThisComponent()
{
	D_ASSERT(IsValid(mOwnerEntity) == true);
	mOwnerEntity->RemoveComponent(this);
}
