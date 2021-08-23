#include "BoxCollider3D.h"
#include <Transform.h>

void doom::BoxCollider3D::UpdateLocalCollider()
{
	mLocalAABB3D.mLowerBound = mOffset - mHalfExtent;
	mLocalAABB3D.mUpperBound = mOffset + mHalfExtent;
}

void doom::BoxCollider3D::UpdateWorldCollider()
{
	physics::AABB3D::ApplyModelMatrix(mLocalAABB3D, GetTransform()->GetModelMatrix(), mWorldAABB3D);
}


void doom::BoxCollider3D::SetFromAABB3D(const physics::AABB3D& aabb3D)
{
	mOffset = (aabb3D.mLowerBound + aabb3D.mUpperBound) * 0.5f;
	mHalfExtent = (aabb3D.mUpperBound - aabb3D.mLowerBound) * 0.5f;
	bmIsLocalColliderDirty = true;
}

void doom::BoxCollider3D::SetHalfExtent(const math::Vector3& halfExtent)
{
	mHalfExtent = halfExtent;
	bmIsLocalColliderDirty = true;
}

math::Vector3 doom::BoxCollider3D::GetHalfExtent() const
{
	return mHalfExtent;
}

doom::physics::AABB3D doom::BoxCollider3D::ExtractLocalAABB3D()
{
	return mLocalAABB3D;
}



doom::physics::Collider* doom::BoxCollider3D::GetWorldCollider()
{
	return &(mWorldAABB3D);
}



void doom::BoxCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	SetFromAABB3D(aabb3dFromMesh);
}
