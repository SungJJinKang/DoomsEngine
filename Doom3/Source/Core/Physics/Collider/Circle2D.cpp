#include "Circle2D.h"
#include "../Graphics/DebugGraphics.h"
#include <utility>
#include <Vector2.h>

void doom::physics::Circle2D::Render(eColor color)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	const float intervalRadian = math::PI * 2 / 72.0f;

	math::Vector2 exPoint{ this->mCenter + math::Vector2::right * mRadius};
	for (float radian = 0; radian < math::PI * 2; radian += intervalRadian)
	{
		math::Vector2 thirdPoint
		{
			this->mCenter.x + this->mRadius * math::cos(radian + intervalRadian),
			this->mCenter.y + this->mRadius * math::sin(radian + intervalRadian)
		};
		debugGraphics->DebugDraw2DTriangle(this->mCenter, exPoint, thirdPoint, color, true);

		exPoint = thirdPoint;
	}
}

doom::physics::Circle2D::Circle2D(const math::Vector2& center, float radius)
	:mCenter{ center }, mRadius{ radius }
{
}

doom::physics::Collider::ColliderType doom::physics::Circle2D::GetColliderType() const
{
	return doom::physics::Collider::ColliderType::Circle2D;
}
