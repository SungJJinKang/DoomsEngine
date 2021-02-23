#include "SphereCollider3D.h"
#include <Transform.h>
void doom::SphereCollider3D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mSpere.mCenter = pos + this->mOffset;
	this->mSpere.mRadius = this->mRadius;
}

void doom::SphereCollider3D::_UpdatePhysics()
{

}


void doom::SphereCollider3D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsCorePhysicsVariableDirty = true;
}

float doom::SphereCollider3D::GetRadius()
{
	return this->mRadius;
}
