#include "CapsuleCollider3D.h"
#include <Transform.h>

#include <Utility.h>

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



void doom::CapsuleCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	this->mHeight = (aabb3dFromMesh.mUpperBound.y - aabb3dFromMesh.mLowerBound.y);
	this->mRadius = aabb3dFromMesh.GetDiagonarLineLength();
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

doom::physics::AABB3D doom::CapsuleCollider3D::ExtractLocalAABB3D()
{
	float height = math::Max(this->mLocalCapsuleCollider.mHeight / 2.0f, this->mLocalCapsuleCollider.mRadius);

	math::Vector3 lowerBound
	{
		this->mLocalCapsuleCollider.mCenter.x - this->mLocalCapsuleCollider.mRadius,
		this->mLocalCapsuleCollider.mCenter.y - height,
		this->mLocalCapsuleCollider.mCenter.z - this->mLocalCapsuleCollider.mRadius
	};

	math::Vector3 upperBound
	{
		this->mLocalCapsuleCollider.mCenter.x + this->mLocalCapsuleCollider.mRadius,
		this->mLocalCapsuleCollider.mCenter.y + height,
		this->mLocalCapsuleCollider.mCenter.z + this->mLocalCapsuleCollider.mRadius
	};

	return doom::physics::AABB3D(lowerBound, upperBound);
}



doom::physics::Collider* doom::CapsuleCollider3D::GetWorldCollider()
{
	return &(this->mWorldCapsuleCollider);
}

