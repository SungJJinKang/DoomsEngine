#include "Collider2D.h"

void doom::Collider2D::SetOffset(const math::Vector2& offset)
{
	this->mOffset = offset;
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector2 doom::Collider2D::GetOffset()
{
	return this->mOffset;
}
