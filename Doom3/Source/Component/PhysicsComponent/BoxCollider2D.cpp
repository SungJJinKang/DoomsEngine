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

	physics::ApplyModelMatrixToAABB2D(this->mLocalAABB2D, transform->GetModelMatrix(), this->mWorldAABB2D);
}


void doom::BoxCollider2D::SetAABB2D(const physics::AABB2D& aabb2D)
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

doom::physics::Collider* doom::BoxCollider2D::GetWorldCollider()
{
	return &(this->mWorldAABB2D);
}

void doom::BoxCollider2D::AutoColliderSetting()
{
	physics::AABB3D aabb3d{};
	bool isHaveMeshAABB3D = this->GetMeshAABB3D(aabb3d);
	if (isHaveMeshAABB3D == true)
	{
		this->SetAABB2D(aabb3d);
	}
}
