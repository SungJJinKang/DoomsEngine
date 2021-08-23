#include "Collider3DComponent.h"

math::Vector3 doom::Collider3DComponent::GetOffsetVector3() const
{
	return mOffset;
}

void doom::Collider3DComponent::SetOffset(const math::Vector3& offset)
{
	mOffset = offset;
	bmIsLocalColliderDirty = true;
}

math::Vector3 doom::Collider3DComponent::GetOffset()
{
	return mOffset;
}
