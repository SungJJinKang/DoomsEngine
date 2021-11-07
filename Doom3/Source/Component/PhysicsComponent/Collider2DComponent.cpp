#include "Collider2DComponent.h"

math::Vector3 dooms::Collider2DComponent::GetOffsetVector3() const
{
	return mOffset;
}

void dooms::Collider2DComponent::SetOffset(const math::Vector2& offset)
{
	mOffset = offset;
	bmIsLocalColliderDirty = true;
}

math::Vector2 dooms::Collider2DComponent::GetOffset()
{
	return mOffset;
}
