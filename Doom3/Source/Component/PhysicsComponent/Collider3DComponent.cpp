#include "Collider3DComponent.h"

math::Vector3 dooms::Collider3DComponent::GetOffsetVector3() const
{
	return mOffset;
}

dooms::Collider3DComponent::~Collider3DComponent()
{
}

void dooms::Collider3DComponent::SetOffset(const math::Vector3& offset)
{
	mOffset = offset;
	bmIsLocalColliderDirty = true;
}

math::Vector3 dooms::Collider3DComponent::GetOffset()
{
	return mOffset;
}
