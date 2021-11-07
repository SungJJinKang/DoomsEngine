#include "CapsuleCollider.h"

dooms::physics::CapsuleCollider::CapsuleCollider(const math::Vector3& center, FLOAT32 height, FLOAT32 radius)
	: mCenter{ center }, mHeight{ height }, mRadius{ radius }
{

}

dooms::physics::ColliderType dooms::physics::CapsuleCollider::GetColliderType() const
{
	return dooms::physics::ColliderType::CapsuleCollider;
}

void dooms::physics::CapsuleCollider::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
	//throw std::logic_error("The method or operation is not implemented.");
}
