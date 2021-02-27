#include "BoxCollider2D.h"
#include <Transform.h>
void doom::BoxCollider2D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mAABB2D.mLowerBound = pos + this->mOffset - this->mHalfExtent;
	this->mAABB2D.mUpperBound = pos + this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider2D::SolveCollision()
{

}

void doom::BoxCollider2D::SetAABB2D(const physics::AABB2D& aabb2D)
{
	this->mAABB2D = aabb2D;
	this->UpdateHalfExtent();
}

void doom::BoxCollider2D::UpdateHalfExtent()
{
	this->mHalfExtent = this->mAABB2D.GetHalfExtent();
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector2 doom::BoxCollider2D::GetHalfExtent()
{
	return this->mHalfExtent;
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
