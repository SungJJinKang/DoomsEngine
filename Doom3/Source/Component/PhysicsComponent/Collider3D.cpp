#include "Collider3D.h"

void doom::Collider3D::SetOffset(const math::Vector3& offset)
{
	this->mOffset = offset;
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector3 doom::Collider3D::GetOffset()
{
	return this->mOffset;
}
