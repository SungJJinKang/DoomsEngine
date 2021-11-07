#include "SphereCollider3D.h"
#include <Transform.h>

void dooms::SphereCollider3D::UpdateLocalCollider()
{
	mLocalSpere.mCenter = mOffset;
	mLocalSpere.mRadius = mRadius;
}

void dooms::SphereCollider3D::UpdateWorldCollider()
{
	auto transform = GetTransform();
	auto translate = transform->GetPosition();
	auto scale = transform->GetScale();

	mWorldSpere.mCenter = mOffset + translate;
	mWorldSpere.mRadius = mRadius * math::Max(math::Max(scale.x, scale.y), scale.z);
}

void dooms::SphereCollider3D::SetRadius(FLOAT32 radius)
{
	mRadius = radius;
	bmIsLocalColliderDirty = true;
}

FLOAT32 dooms::SphereCollider3D::GetRadius()
{
	return mRadius;
}

dooms::physics::AABB3D dooms::SphereCollider3D::ExtractLocalAABB3D()
{
	math::Vector3 lowerBound
	{
		mLocalSpere.mCenter.x - mLocalSpere.mRadius,
		mLocalSpere.mCenter.y - mLocalSpere.mRadius,
		mLocalSpere.mCenter.z - mLocalSpere.mRadius
	};

	math::Vector3 upperBound
	{
		mLocalSpere.mCenter.x + mLocalSpere.mRadius,
		mLocalSpere.mCenter.y + mLocalSpere.mRadius,
		mLocalSpere.mCenter.z + mLocalSpere.mRadius
	};

	return dooms::physics::AABB3D(lowerBound, upperBound);
}

dooms::physics::Collider* dooms::SphereCollider3D::GetWorldCollider()
{
	return &(mWorldSpere);
}

void dooms::SphereCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D & aabb3dFromMesh)
{
	mRadius = aabb3dFromMesh.GetDiagonarLineLength();	
}
