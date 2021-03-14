#include "SphereCollider3D.h"
#include <Transform.h>

void doom::SphereCollider3D::UpdateLocalCollider()
{
	this->mLocalSpere.mCenter = this->mOffset;
	this->mLocalSpere.mRadius = this->mRadius;
}

void doom::SphereCollider3D::UpdateWorldCollider()
{
	auto transform = this->GetTransform();
	auto translate = transform->GetPosition();
	auto scale = transform->GetScale();

	this->mWorldSpere.mCenter = this->mOffset + translate;
	this->mWorldSpere.mRadius = this->mRadius * math::Max(math::Max(scale.x, scale.y), scale.z);
}

void doom::SphereCollider3D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsLocalColliderDirty = true;
}

float doom::SphereCollider3D::GetRadius()
{
	return this->mRadius;
}

doom::physics::AABB3D doom::SphereCollider3D::ExtractLocalAABB3D()
{
	math::Vector3 lowerBound
	{
		this->mLocalSpere.mCenter.x - this->mLocalSpere.mRadius,
		this->mLocalSpere.mCenter.y - this->mLocalSpere.mRadius,
		this->mLocalSpere.mCenter.z - this->mLocalSpere.mRadius
	};

	math::Vector3 upperBound
	{
		this->mLocalSpere.mCenter.x + this->mLocalSpere.mRadius,
		this->mLocalSpere.mCenter.y + this->mLocalSpere.mRadius,
		this->mLocalSpere.mCenter.z + this->mLocalSpere.mRadius
	};

	return doom::physics::AABB3D(lowerBound, upperBound);
}

doom::physics::Collider* doom::SphereCollider3D::GetWorldCollider()
{
	return &(this->mWorldSpere);
}

void doom::SphereCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D & aabb3dFromMesh)
{
	this->mRadius = aabb3dFromMesh.GetDiagonarLineLength();	
}
