#include "Collider.h"

void doom::Collider::ResetAllState()
{
	this->mbIsColliderEnter = false;
	this->mbIsColliderExit = false;
	this->mbIsColliderStay = false;

	this->mbIsTriggerEnter = false;
	this->mbIsTriggerExit = false;
	this->mbIsTriggerStay = false;
}

void doom::Collider::InitComponent()
{
}

void doom::Collider::UpdateComponent()
{
	this->UpdatePhysics();
}

void doom::Collider::OnEndOfFrame_Component()
{

}

void doom::Collider::OnDestroy()
{
	this->ResetAllState();
}

void doom::Collider::OnActivated()
{
	this->ResetAllState();
}

void doom::Collider::OnDeActivated()
{
	this->ResetAllState();
}

void doom::Collider::UpdatePhysics()
{
	if (this->bmIsCorePhysicsVariableDirty == true)
	{
		this->UpdateCorePhysicsVariable();
		this->bmIsCorePhysicsVariableDirty = false;
	}

	this->_UpdatePhysics();



}

