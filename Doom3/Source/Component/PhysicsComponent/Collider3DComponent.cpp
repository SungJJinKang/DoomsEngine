#include "Collider3DComponent.h"

math::Vector3 doom::Collider3DComponent::GetOffsetVector3() const
{
	return this->mOffset;
}

void doom::Collider3DComponent::SetOffset(const math::Vector3& offset)
{
	this->mOffset = offset;
	this->bmIsLocalColliderDirty = true;
}

math::Vector3 doom::Collider3DComponent::GetOffset()
{
	return this->mOffset;
}
