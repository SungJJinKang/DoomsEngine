#include "BoxCollider2D.h"
#include <Transform.h>

void doom::BoxCollider2D::UpdateLocalCollider()
{
	this->mLocalAABB2D.mLowerBound = this->mOffset - this->mHalfExtent;
	this->mLocalAABB2D.mUpperBound = this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider2D::UpdateWorldCollider()
{
	auto transform = this->GetTransform();

	physics::ApplyModelMatrixToAABB(this->mLocalAABB2D, transform->GetModelMatrix(), this->mWorldAABB2D);
}


void doom::BoxCollider2D::SetFromAABB2D(const physics::AABB2D& aabb2D)
{
	this->mOffset = (aabb2D.mLowerBound + aabb2D.mUpperBound) * 0.5f;
	this->mHalfExtent = (aabb2D.mUpperBound - aabb2D.mLowerBound) * 0.5f;
	this->bmIsLocalColliderDirty = true;
}

void doom::BoxCollider2D::SetHalfExtent(const math::Vector2& halfExtent)
{
	this->mHalfExtent = halfExtent;
	this->bmIsLocalColliderDirty = true;
}

math::Vector2 doom::BoxCollider2D::GetHalfExtent() const
{
	return this->mHalfExtent;
}

doom::physics::AABB3D doom::BoxCollider2D::ExtractLocalAABB3D()
{
	return this->mLocalAABB2D;
}

doom::physics::Collider* doom::BoxCollider2D::GetWorldCollider()
{
	return &(this->mWorldAABB2D);
}

void doom::BoxCollider2D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	this->SetFromAABB2D(aabb3dFromMesh);
}
