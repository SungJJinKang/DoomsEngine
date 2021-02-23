#include "CapsuleCollider3D.h"
#include <Transform.h>
void doom::CapsuleCollider3D::UpdateCorePhysicsVariable()
{
	this->mCapsuleCollider.mCenter = this->GetTransform()->GetPosition() + this->mOffset;
	this->mCapsuleCollider.mRadius = this->mRadius;
	this->mCapsuleCollider.mHeight = this->mHeight;
}

void doom::CapsuleCollider3D::_UpdatePhysics()
{

}


void doom::CapsuleCollider3D::SetHeight(float height)
{
	this->mHeight = height;
	this->bmIsCorePhysicsVariableDirty = true;
}

float doom::CapsuleCollider3D::GetHeight()
{
	return this->mHeight;
}

void doom::CapsuleCollider3D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsCorePhysicsVariableDirty = true;
}

float doom::CapsuleCollider3D::GetRadius()
{
	return this->mRadius;
}
