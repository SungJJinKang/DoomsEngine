#include "Component.h"
#include "../../Core/Scene/Entity.h"
#include "../Transform.h"

using namespace doom;






Component::Component() : bIsAddedToEntity{}, mOwnerEntity{}, mTransform{}, mIsActivated{}
{

}

Component::~Component() // Never put parameter to component Destructor (including derived class)
{

}

void doom::Component::InitComponent_Internal(Entity* entity)
{
	D_ASSERT(bIsAddedToEntity == false);
	mOwnerEntity = entity;
	mTransform = entity->GetTransform();
	bIsAddedToEntity = true;
}

void doom::Component::UpdateComponent_Internal()
{
}


void doom::Component::OnEndOfFrame_Component_Internal()
{

	this->FrameDirtyChecker_EndOfFrame();
}

void doom::Component::OnDestroy_Internal()
{
}

void doom::Component::OnActivated_Internal()
{
}

void doom::Component::OnDeActivated_Internal()
{
}

unsigned int Component::GetOwnerEntityLayerIndex() const
{
	return this->GetOwnerEntity()->GetLayerIndex();
}

doom::Entity* Component::GetOwnerEntity() const
{
	return this->mOwnerEntity;
}

doom::Transform* Component::GetTransform() const
{
	return this->mTransform;
}

