#include "Collider2DComponent.h"

const math::Vector3& doom::Collider2DComponent::GetOffsetVector3() const
{
	return this->mOffset;
}

void doom::Collider2DComponent::SetOffset(const math::Vector2& offset)
{
	this->mOffset = offset;
	this->bmIsLocalColliderDirty = true;
}

math::Vector2 doom::Collider2DComponent::GetOffset()
{
	return this->mOffset;
}
