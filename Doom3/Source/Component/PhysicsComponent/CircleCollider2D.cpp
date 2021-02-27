#include "CircleCollider2D.h"
#include <Transform.h>
void doom::CircleCollider2D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mCircle2D.mCenter = pos + this->mOffset;
	this->mCircle2D.mRadius = this->mRadius;
}

void doom::CircleCollider2D::SolveCollision()
{

}


void doom::CircleCollider2D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsCorePhysicsVariableDirty = true;
}

float doom::CircleCollider2D::GetRadius()
{
	return this->mRadius;
}

void doom::CircleCollider2D::AutoColliderSetting()
{
	physics::AABB3D aabb3d{};
	bool isHaveMeshAABB3D = this->GetMeshAABB3D(aabb3d);
	if (isHaveMeshAABB3D == true)
	{
		this->mRadius = aabb3d.GetDiagonarLineLength();
	}
}
