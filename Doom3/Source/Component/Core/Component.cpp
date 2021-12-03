#include "Component.h"
#include "../../Core/Scene/Entity.h"
#include "../Transform.h"

using namespace dooms;


void Component::OnSetPendingKill()
{
	Base::OnSetPendingKill();

	OnDestroy_Internal();
	OnDestroy();
}

Component::Component() : bIsAddedToEntity{false}, mOwnerEntity{nullptr}, mTransform{nullptr}, mIsActivated{true}
{
	SetDObjectFlag(eDObjectFlag::NotCollectedByGC);
}

Component::~Component()
{
	D_ASSERT(IsStrongValid(mOwnerEntity) == true);
}

Component::Component(const Component&)
	: bIsAddedToEntity{ false }, mOwnerEntity{ nullptr }, mTransform{nullptr}, mIsActivated{ true }
{
	SetDObjectFlag(eDObjectFlag::NotCollectedByGC);
}

Component& Component::operator=(const Component&)
{
	bIsAddedToEntity = false;
	mOwnerEntity = nullptr;
	mTransform = nullptr;
	mIsActivated = false;

	SetDObjectFlag(eDObjectFlag::NotCollectedByGC);

	return *this;
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
