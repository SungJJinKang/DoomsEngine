#include "CapsuleCollider.h"

doom::physics::CapsuleCollider::CapsuleCollider(const math::Vector3& center, float height, float radius)
	: mCenter{ center }, mHeight{ height }, mRadius{ radius }
{

}

doom::physics::ColliderType doom::physics::CapsuleCollider::GetColliderType() const
{
	return doom::physics::ColliderType::CapsuleCollider;
}

void doom::physics::CapsuleCollider::Render(eColor color)
{
	//throw std::logic_error("The method or operation is not implemented.");
}
