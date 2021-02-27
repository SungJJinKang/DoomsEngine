#include "SphereCollider3D.h"
#include <Transform.h>
void doom::SphereCollider3D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mSpere.mCenter = pos + this->mOffset;
	this->mSpere.mRadius = this->mRadius;
}

void doom::SphereCollider3D::SolveCollision()
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

void doom::SphereCollider3D::AutoColliderSetting()
{
	physics::AABB3D aabb3d{};
	bool isHaveMeshAABB3D =	this->GetMeshAABB3D(aabb3d);
	if (isHaveMeshAABB3D == true)
	{
		this->mRadius = aabb3d.GetDiagonarLineLength();
	}
}
