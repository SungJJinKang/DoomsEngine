#include "CapsuleCollider3D.h"
#include <Transform.h>

#include <Utility.h>

void dooms::CapsuleCollider3D::UpdateLocalCollider()
{
	mLocalCapsuleCollider.mCenter = mOffset;
	mLocalCapsuleCollider.mRadius = mRadius;
	mLocalCapsuleCollider.mHeight = mHeight;
}

void dooms::CapsuleCollider3D::UpdateWorldCollider()
{
	auto transform = GetTransform();
	auto translate = transform->GetPosition();
	auto scale = transform->GetScale();

	mWorldCapsuleCollider.mCenter = mOffset + translate;
	mWorldCapsuleCollider.mRadius = mRadius * scale.x;
	mWorldCapsuleCollider.mHeight = mHeight * scale.y;
}



void dooms::CapsuleCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	mHeight = (aabb3dFromMesh.mUpperBound.y - aabb3dFromMesh.mLowerBound.y);
	mRadius = aabb3dFromMesh.GetDiagonarLineLength();
}


void dooms::CapsuleCollider3D::SetHeight(FLOAT32 height)
{
	mHeight = height;
	bmIsLocalColliderDirty = true;
}

FLOAT32 dooms::CapsuleCollider3D::GetHeight()
{
	return mHeight;
}

void dooms::CapsuleCollider3D::SetRadius(FLOAT32 radius)
{
	mRadius = radius;
	bmIsLocalColliderDirty = true;
}

FLOAT32 dooms::CapsuleCollider3D::GetRadius()
{
	return mRadius;
}

dooms::physics::AABB3D dooms::CapsuleCollider3D::ExtractLocalAABB3D()
{
	FLOAT32 height = math::Max(mLocalCapsuleCollider.mHeight / 2.0f, mLocalCapsuleCollider.mRadius);

	math::Vector3 lowerBound
	{
		mLocalCapsuleCollider.mCenter.x - mLocalCapsuleCollider.mRadius,
		mLocalCapsuleCollider.mCenter.y - height,
		mLocalCapsuleCollider.mCenter.z - mLocalCapsuleCollider.mRadius
	};

	math::Vector3 upperBound
	{
		mLocalCapsuleCollider.mCenter.x + mLocalCapsuleCollider.mRadius,
		mLocalCapsuleCollider.mCenter.y + height,
		mLocalCapsuleCollider.mCenter.z + mLocalCapsuleCollider.mRadius
	};

	return dooms::physics::AABB3D(lowerBound, upperBound);
}



dooms::physics::Collider* dooms::CapsuleCollider3D::GetWorldCollider()
{
	return &(mWorldCapsuleCollider);
}

