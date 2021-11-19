#include "Circle2D.h"
#include <Graphics/DebugGraphics/DebugDrawer.h>
#include <Vector2.h>

void dooms::physics::Circle2D::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	const FLOAT32 intervalRadian = math::PI * 2 / 72.0f;

	math::Vector2 exPoint{ mCenter + math::Vector2::right * mRadius};
	for (FLOAT32 radian = 0; radian < math::PI * 2; radian += intervalRadian)
	{
		math::Vector3 newPoint
		{
			mCenter.x + mRadius * std::cos(radian + intervalRadian),
			mCenter.y + mRadius * std::sin(radian + intervalRadian),
			0
		};
		debugGraphics->DebugDraw2DLine(newPoint, math::Vector3{ exPoint }, color, drawInstantly);

		exPoint = newPoint;
	}
#endif
}

dooms::physics::Circle2D::Circle2D(const math::Vector2& center, FLOAT32 radius)
	:mCenter{ center }, mRadius{ radius }
{
}

dooms::physics::ColliderType dooms::physics::Circle2D::GetColliderType() const
{
	return dooms::physics::ColliderType::Circle2D;
}

bool dooms::physics::IsOverlapCircle2DAndCircle2D(const Circle2D& circle2d1, const Circle2D& circle2d2)
{
	FLOAT32 distanceSqr{ (circle2d1.mCenter - circle2d2.mCenter).sqrMagnitude() };
	return distanceSqr < std::pow(circle2d1.mRadius + circle2d2.mRadius, 2);
}

bool dooms::physics::IsOverlapCircle2DAndCircle2D(const Collider* const circle2d1, const Collider* const circle2d2)
{
	return IsOverlapCircle2DAndCircle2D(*static_cast<const Circle2D*>(circle2d1), *static_cast<const Circle2D*>(circle2d2));
}
