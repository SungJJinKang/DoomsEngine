#include "Collider2DComponent.h"

void doom::Collider2DComponent::SetOffset(const math::Vector2& offset)
{
	this->mOffset = offset;
	this->bmIsLocalColliderDirty = true;
}

math::Vector2 doom::Collider2DComponent::GetOffset()
{
	return this->mOffset;
}
