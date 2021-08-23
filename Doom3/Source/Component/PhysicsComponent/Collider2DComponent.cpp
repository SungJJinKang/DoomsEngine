#include "Collider2DComponent.h"

math::Vector3 doom::Collider2DComponent::GetOffsetVector3() const
{
	return mOffset;
}

void doom::Collider2DComponent::SetOffset(const math::Vector2& offset)
{
	mOffset = offset;
	bmIsLocalColliderDirty = true;
}

math::Vector2 doom::Collider2DComponent::GetOffset()
{
	return mOffset;
}
