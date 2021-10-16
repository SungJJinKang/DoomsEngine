#include "Component.h"
#include "../../Core/Scene/Entity.h"
#include "../Transform.h"

using namespace doom;






Component::Component() : bIsAddedToEntity{}, mOwnerEntity{}, mTransform{}, mIsActivated{}
{

}

Component::~Component()
{
}

void Component::AddLocalDirtyToTransformDirtyReceiver(DirtyReceiver& localDirty)
{
	GetTransform()->mDirtySender.AddDirtyReceiver(&localDirty);
}

void doom::Component::InitComponent_Internal(Entity* entity)
{
	mOwnerEntity = entity;
	mTransform = entity->GetTransform();
	bIsAddedToEntity = true;
}

void doom::Component::UpdateComponent_Internal()
{
}


void Component::FixedUpdateComponent_Internal()
{

}

void doom::Component::OnEndOfFrame_Component_Internal()
{
	FrameDirtyChecker_EndOfFrame();
}

void doom::Component::OnDestroy_Internal()
{
}

void doom::Component::OnActivated_Internal()
{
	SetDirtyTrueAtThisFrame();
}

void doom::Component::OnDeActivated_Internal()
{
}

UINT32 Component::GetOwnerEntityLayerIndex() const
{
	return GetOwnerEntity()->GetLayerIndex();
}
