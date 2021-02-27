#include "ColliderComponent.h"

#include <Entity.h>
#include "../Renderer.h"

void doom::ColliderComponent::ResetAllCollisionState()
{
	this->mbIsColliderEnter = false;
	this->mbIsColliderExit = false;
	this->mbIsColliderStay = false;

	this->mbIsTriggerEnter = false;
	this->mbIsTriggerExit = false;
	this->mbIsTriggerStay = false;
}

void doom::ColliderComponent::InitComponent()
{
	this->CreateTransformDirtyReceiver();
	this->AddLocalDirtyToTransformDirtyReceiver(this->bmIsCorePhysicsVariableDirty);

	this->AutoColliderSetting();
}

void doom::ColliderComponent::UpdateComponent()
{
	this->UpdatePhysics();
}

void doom::ColliderComponent::OnEndOfFrame_Component()
{

}

void doom::ColliderComponent::OnDestroy()
{
	this->ResetAllCollisionState();
}

void doom::ColliderComponent::OnActivated()
{
	this->ResetAllCollisionState();
}

void doom::ColliderComponent::OnDeActivated()
{
	this->ResetAllCollisionState();
}

bool doom::ColliderComponent::GetMeshAABB3D(physics::AABB3D& aabb3D)
{
	const Renderer* renderer = this->GetOwnerEntity()->GetComponent<Renderer>();
	if (renderer != nullptr)
	{
		aabb3D = renderer->GetLocalAABB3D();
		return true;
	}
	else
	{
		return false;
	}
}

void doom::ColliderComponent::OnPreUpdatePhysics()
{
	this->ResetAllCollisionState();

	if (this->bmIsCorePhysicsVariableDirty.GetIsDirty(true))
	{
		this->UpdateCorePhysicsVariable();
	}
}

void doom::ColliderComponent::UpdatePhysics()
{
	this->SolveCollision();
}

void doom::ColliderComponent::OnPostUpdatePhysics()
{

}

