#include "CircleCollider2D.h"
#include <Transform.h>
void doom::CircleCollider2D::UpdateCorePhysicsVariable()
{
	math::Vector2 pos = this->GetTransform()->GetPosition();
	this->mCircle2D.mCenter = pos + this->mOffset;
	this->mCircle2D.mRadius = this->mRadius;
}

void doom::CircleCollider2D::_UpdatePhysics()
{

}


void doom::CircleCollider2D::SetRadius(float radius)
{
	this->mRadius = radius;
	this->bmIsCorePhysicsVariableDirty = true;
}

float doom::CircleCollider2D::GetRadius()
{
	return this->mRadius;
}
