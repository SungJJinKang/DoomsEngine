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

doom::physics::Collider* doom::SphereCollider3D::GetWorldCollider()
{
	return &(this->mWorldSpere);
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
