#include "Collider3DComponent.h"

void doom::Collider3DComponent::SetOffset(const math::Vector3& offset)
{
	this->mOffset = offset;
	this->bmIsCorePhysicsVariableDirty = true;
}

math::Vector3 doom::Collider3DComponent::GetOffset()
{
	return this->mOffset;
}
