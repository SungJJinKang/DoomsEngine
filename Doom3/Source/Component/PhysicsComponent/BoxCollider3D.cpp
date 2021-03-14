#include "BoxCollider3D.h"
#include <Transform.h>

void doom::BoxCollider3D::UpdateLocalCollider()
{
	this->mLocalAABB3D.mLowerBound = this->mOffset - this->mHalfExtent;
	this->mLocalAABB3D.mUpperBound = this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider3D::UpdateWorldCollider()
{
	physics::ApplyModelMatrixToAABB(this->mLocalAABB3D, this->GetTransform()->GetModelMatrix(), this->mWorldAABB3D);
}


void doom::BoxCollider3D::SetFromAABB3D(const physics::AABB3D& aabb3D)
{
	this->mOffset = (aabb3D.mLowerBound + aabb3D.mUpperBound) * 0.5f;
	this->mHalfExtent = (aabb3D.mUpperBound - aabb3D.mLowerBound) * 0.5f;
	this->bmIsLocalColliderDirty = true;
}

void doom::BoxCollider3D::SetHalfExtent(const math::Vector3& halfExtent)
{
	this->mHalfExtent = halfExtent;
	this->bmIsLocalColliderDirty = true;
}

math::Vector3 doom::BoxCollider3D::GetHalfExtent() const
{
	return this->mHalfExtent;
}

doom::physics::AABB3D doom::BoxCollider3D::ExtractLocalAABB3D()
{
	return this->mLocalAABB3D;
}



doom::physics::Collider* doom::BoxCollider3D::GetWorldCollider()
{
	return &(this->mWorldAABB3D);
}



void doom::BoxCollider3D::AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh)
{
	this->SetFromAABB3D(aabb3dFromMesh);
}
