#include "SphereCollider3D.h"
#include <Transform.h>

void doom::SphereCollider3D::UpdateLocalCollider()
{
	mLocalSpere.mCenter = mOffset;
	mLocalSpere.mRadius = mRadius;
}

void doom::SphereCollider3D::UpdateWorldCollider()
{
	auto transform = GetTransform();
	auto translate = transform->GetPosition();
	auto scale = transform->GetScale();

	mWorldSpere.mCenter = mOffset + translate;
	mWorldSpere.mRadius = mRadius * math::Max(math::Max(scale.x, scale.y), scale.z);
}

void doom::SphereCollider3D::SetRadius(FLOAT32 radius)
{
	mRadius = radius;
	bmIsLocalColliderDirty = true;
}

FLOAT32 doom::SphereCollider3D::GetRadius()
{
	return mRadius;
}

doom::physics::AABB3D doom::SphereCollider3D::ExtractLocalAABB3D()
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

	return doom::physics::AABB3D(lowerBound, upperBound);
}

doom::physics::Collider* doom::SphereCollider3D::GetWorldCollider()
{
	return &(mWorldSpere);
}

void doom::SphereCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D & aabb3dFromMesh)
{
	mRadius = aabb3dFromMesh.GetDiagonarLineLength();	
}
