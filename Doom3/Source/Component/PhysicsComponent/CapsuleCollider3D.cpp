#include "CapsuleCollider3D.h"
#include <Transform.h>
void doom::CapsuleCollider3D::UpdateCorePhysicsVariable()
{
	this->mCapsuleCollider.mCenter = this->GetTransform()->GetPosition() + this->mOffset;
	this->mCapsuleCollider.mRadius = this->mRadius;
	this->mCapsuleCollider.mHeight = this->mHeight;
}

void doom::CapsuleCollider3D::SolveCollision()
{

}

void doom::CapsuleCollider3D::AutoColliderSetting()
{
	physics::AABB3D aabb3d{};
	bool isHaveMeshAABB3D = this->GetMeshAABB3D(aabb3d);
	if (isHaveMeshAABB3D == true)
	{
		this->mHeight = (aabb3d.mUpperBound.y - aabb3d.mLowerBound.y);
		this->mRadius = aabb3d.GetDiagonarLineLength();
	}
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

