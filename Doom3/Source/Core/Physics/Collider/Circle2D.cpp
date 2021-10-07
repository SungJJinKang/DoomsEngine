#include "Circle2D.h"
#include <Graphics/DebugGraphics/DebugDrawer.h>
#include <utility>
#include <Vector2.h>

void doom::physics::Circle2D::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	const float intervalRadian = math::PI * 2 / 72.0f;

	math::Vector2 exPoint{ mCenter + math::Vector2::right * mRadius};
	for (float radian = 0; radian < math::PI * 2; radian += intervalRadian)
	{
		math::Vector3 newPoint
		{
			mCenter.x + mRadius * math::cos(radian + intervalRadian),
			mCenter.y + mRadius * math::sin(radian + intervalRadian),
			0
		};
		debugGraphics->DebugDraw2DLine(newPoint, exPoint, color, drawInstantly);

		exPoint = newPoint;
	}
#endif
}

doom::physics::Circle2D::Circle2D(const math::Vector2& center, float radius)
	:mCenter{ center }, mRadius{ radius }
{
}

doom::physics::ColliderType doom::physics::Circle2D::GetColliderType() const
{
	return doom::physics::ColliderType::Circle2D;
}

bool doom::physics::IsOverlapCircle2DAndCircle2D(const Circle2D& circle2d1, const Circle2D& circle2d2)
{
	float distanceSqr{ (circle2d1.mCenter - circle2d2.mCenter).sqrMagnitude() };
	return distanceSqr < math::pow(circle2d1.mRadius + circle2d2.mRadius, 2);
}

bool doom::physics::IsOverlapCircle2DAndCircle2D(const Collider* const circle2d1, const Collider* const circle2d2)
{
	return IsOverlapCircle2DAndCircle2D(*static_cast<const Circle2D*>(circle2d1), *static_cast<const Circle2D*>(circle2d2));
}
