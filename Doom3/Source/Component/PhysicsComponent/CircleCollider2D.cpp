#include "CircleCollider2D.h"
#include <Transform.h>

void doom::CircleCollider2D::UpdateLocalCollider()
{
	this->mLocalCircle2D.mCenter = this->mOffset;
	this->mLocalCircle2D.mRadius = this->mRadius;
}

void doom::CircleCollider2D::UpdateWorldCollider()
{
	auto transform = this->GetTransform();
	auto translate = transform->GetPosition();
	translate.z = 0;
	auto scale = transform->GetScale();

	this->mWorldCircle2D.mCenter = this->mOffset + translate;
	this->mWorldCircle2D.mRadius = this->mRadius * math::Max(scale.x, scale.y);
}



void doom::CircleCollider2D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsLocalColliderDirty = true;
}

float doom::CircleCollider2D::GetRadius()
{
	return this->mRadius;
}

doom::physics::AABB3D doom::CircleCollider2D::ExtractLocalAABB3D()
{
	math::Vector3 lowerBound
	{
		this->mLocalCircle2D.mCenter.x - this->mLocalCircle2D.mRadius,
		this->mLocalCircle2D.mCenter.y - this->mLocalCircle2D.mRadius,
		0
	};

	math::Vector3 upperBound
	{
		this->mLocalCircle2D.mCenter.x + this->mLocalCircle2D.mRadius,
		this->mLocalCircle2D.mCenter.y + this->mLocalCircle2D.mRadius,
		0
	};

	return doom::physics::AABB3D(lowerBound, upperBound);
}

doom::physics::Collider* doom::CircleCollider2D::GetWorldCollider()
{
	return &(this->mWorldCircle2D);
}

void doom::CircleCollider2D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	this->mRadius = aabb3dFromMesh.GetDiagonarLineLength();
}
