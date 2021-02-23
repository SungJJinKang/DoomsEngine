#include "BoxCollider3D.h"
#include <Transform.h>
void doom::BoxCollider3D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mAABB3D.mLowerBound = pos + this->mOffset - this->mHalfExtent;
	this->mAABB3D.mUpperBound = pos + this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider3D::_UpdatePhysics()
{

}

void doom::BoxCollider3D::SetHalfExtent(const math::Vector3& halfExtent)
{
	this->mHalfExtent = halfExtent;
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector3 doom::BoxCollider3D::GetHalfExtent()
{
	return this->mHalfExtent;
}
