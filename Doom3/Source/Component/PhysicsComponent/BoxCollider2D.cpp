#include "BoxCollider2D.h"
#include <Transform.h>
void doom::BoxCollider2D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mAABB2D.mLowerBound = pos + this->mOffset - this->mHalfExtent;
	this->mAABB2D.mUpperBound = pos + this->mOffset + this->mHalfExtent;
}

void doom::BoxCollider2D::_UpdatePhysics()
{

}

void doom::BoxCollider2D::SetHalfExtent(const math::Vector2& halfExtent)
{
	this->mHalfExtent = halfExtent;
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector2 doom::BoxCollider2D::GetHalfExtent()
{
	return this->mHalfExtent;
}
