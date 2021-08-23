#include "BoxCollider2D.h"
#include <Transform.h>

void doom::BoxCollider2D::UpdateLocalCollider()
{
	mLocalAABB2D.mLowerBound = mOffset - mHalfExtent;
	mLocalAABB2D.mUpperBound = mOffset + mHalfExtent;
}

void doom::BoxCollider2D::UpdateWorldCollider()
{
	auto transform = GetTransform();

	physics::AABB2D::ApplyModelMatrix(mLocalAABB2D, transform->GetModelMatrix(), mWorldAABB2D);
}


void doom::BoxCollider2D::SetFromAABB2D(const physics::AABB2D& aabb2D)
{
	mOffset = (aabb2D.mLowerBound + aabb2D.mUpperBound) * 0.5f;
	mHalfExtent = (aabb2D.mUpperBound - aabb2D.mLowerBound) * 0.5f;
	bmIsLocalColliderDirty = true;
}

void doom::BoxCollider2D::SetHalfExtent(const math::Vector2& halfExtent)
{
	mHalfExtent = halfExtent;
	bmIsLocalColliderDirty = true;
}

math::Vector2 doom::BoxCollider2D::GetHalfExtent() const
{
	return mHalfExtent;
}

doom::physics::AABB3D doom::BoxCollider2D::ExtractLocalAABB3D()
{
	return mLocalAABB2D;
}

doom::physics::Collider* doom::BoxCollider2D::GetWorldCollider()
{
	return &(mWorldAABB2D);
}

void doom::BoxCollider2D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	SetFromAABB2D(aabb3dFromMesh);
}
