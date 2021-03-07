#include "BoxCollider3D.h"
#include <Transform.h>

void doom::BoxCollider3D::UpdateLocalCollider()
{
	this->mLocalAABB3D.mLowerBound = this->mOffset - this->mHalfExtent;
	this->mLocalAABB3D.mUpperBound = this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider3D::UpdateWorldCollider()
{
	auto transform = this->GetTransform();

	physics::ApplyModelMatrixToAABB3D(this->mLocalAABB3D, transform->GetModelMatrix(), this->mWorldAABB3D);
}


void doom::BoxCollider3D::SetAABB3D(const physics::AABB3D& aabb3D)
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

doom::physics::Collider* doom::BoxCollider3D::GetWorldCollider()
{
	return &(this->mWorldAABB3D);
}

void doom::BoxCollider3D::AutoColliderSetting()
{
	physics::AABB3D aabb3d{};
	bool isHaveMeshAABB3D = this->GetMeshAABB3D(aabb3d);
	if (isHaveMeshAABB3D == true)
	{
		this->SetAABB3D(aabb3d);
	}
}
