#include "BoxCollider3D.h"
#include <Transform.h>
void doom::BoxCollider3D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mAABB3D.mLowerBound = pos + this->mOffset - this->mHalfExtent;
	this->mAABB3D.mUpperBound = pos + this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider3D::SolveCollision()
{

}

void doom::BoxCollider3D::SetAABB3D(const physics::AABB3D& aabb3D)
{
	this->mAABB3D = aabb3D;
	this->UpdateHalfExtent();
}

void doom::BoxCollider3D::UpdateHalfExtent()
{
	this->mHalfExtent = this->mAABB3D.GetHalfExtent();
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector3 doom::BoxCollider3D::GetHalfExtent()
{
	return this->mHalfExtent;
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
