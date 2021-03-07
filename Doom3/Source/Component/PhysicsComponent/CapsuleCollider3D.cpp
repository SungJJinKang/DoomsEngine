#include "CapsuleCollider3D.h"
#include <Transform.h>

void doom::CapsuleCollider3D::UpdateLocalCollider()
{
	this->mLocalCapsuleCollider.mCenter = this->mOffset;
	this->mLocalCapsuleCollider.mRadius = this->mRadius;
	this->mLocalCapsuleCollider.mHeight = this->mHeight;
}

void doom::CapsuleCollider3D::UpdateWorldCollider()
{
	auto transform = this->GetTransform();
	auto translate = transform->GetPosition();
	auto scale = transform->GetScale();

	this->mWorldCapsuleCollider.mCenter = this->mOffset + translate;
	this->mWorldCapsuleCollider.mRadius = this->mRadius * scale.x;
	this->mWorldCapsuleCollider.mHeight = this->mHeight * scale.y;
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
	this->bmIsLocalColliderDirty = true;
}

float doom::CapsuleCollider3D::GetHeight()
{
	return this->mHeight;
}

void doom::CapsuleCollider3D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsLocalColliderDirty = true;
}

float doom::CapsuleCollider3D::GetRadius()
{
	return this->mRadius;
}

doom::physics::Collider* doom::CapsuleCollider3D::GetWorldCollider()
{
	return &(this->mWorldCapsuleCollider);
}

