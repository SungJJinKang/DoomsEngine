#include "BoxCollider3D.h"
#include <Transform.h>

void dooms::BoxCollider3D::UpdateLocalCollider()
{
	mLocalAABB3D.mLowerBound = mOffset - mHalfExtent;
	mLocalAABB3D.mUpperBound = mOffset + mHalfExtent;
}

void dooms::BoxCollider3D::UpdateWorldCollider()
{
	physics::AABB3D::ApplyModelMatrix(mLocalAABB3D, GetTransform()->GetModelMatrix(), mWorldAABB3D);
}


void dooms::BoxCollider3D::SetFromAABB3D(const physics::AABB3D& aabb3D)
{
	mOffset = (aabb3D.mLowerBound + aabb3D.mUpperBound) * 0.5f;
	mHalfExtent = (aabb3D.mUpperBound - aabb3D.mLowerBound) * 0.5f;
	bmIsLocalColliderDirty = true;
}

void dooms::BoxCollider3D::SetHalfExtent(const math::Vector3& halfExtent)
{
	mHalfExtent = halfExtent;
	bmIsLocalColliderDirty = true;
}

math::Vector3 dooms::BoxCollider3D::GetHalfExtent() const
{
	return mHalfExtent;
}

dooms::physics::AABB3D dooms::BoxCollider3D::ExtractLocalAABB3D()
{
	return mLocalAABB3D;
}



dooms::physics::Collider* dooms::BoxCollider3D::GetWorldCollider()
{
	return &(mWorldAABB3D);
}



void dooms::BoxCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	SetFromAABB3D(aabb3dFromMesh);
}
