#include "CapsuleCollider3D.h"
#include <Transform.h>

#include <Utility.h>

void doom::CapsuleCollider3D::UpdateLocalCollider()
{
	mLocalCapsuleCollider.mCenter = mOffset;
	mLocalCapsuleCollider.mRadius = mRadius;
	mLocalCapsuleCollider.mHeight = mHeight;
}

void doom::CapsuleCollider3D::UpdateWorldCollider()
{
	auto transform = GetTransform();
	auto translate = transform->GetPosition();
	auto scale = transform->GetScale();

	mWorldCapsuleCollider.mCenter = mOffset + translate;
	mWorldCapsuleCollider.mRadius = mRadius * scale.x;
	mWorldCapsuleCollider.mHeight = mHeight * scale.y;
}



void doom::CapsuleCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	mHeight = (aabb3dFromMesh.mUpperBound.y - aabb3dFromMesh.mLowerBound.y);
	mRadius = aabb3dFromMesh.GetDiagonarLineLength();
}


void doom::CapsuleCollider3D::SetHeight(FLOAT32 height)
{
	mHeight = height;
	bmIsLocalColliderDirty = true;
}

FLOAT32 doom::CapsuleCollider3D::GetHeight()
{
	return mHeight;
}

void doom::CapsuleCollider3D::SetRadius(FLOAT32 radius)
{
	mRadius = radius;
	bmIsLocalColliderDirty = true;
}

FLOAT32 doom::CapsuleCollider3D::GetRadius()
{
	return mRadius;
}

doom::physics::AABB3D doom::CapsuleCollider3D::ExtractLocalAABB3D()
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

	return doom::physics::AABB3D(lowerBound, upperBound);
}



doom::physics::Collider* doom::CapsuleCollider3D::GetWorldCollider()
{
	return &(mWorldCapsuleCollider);
}

