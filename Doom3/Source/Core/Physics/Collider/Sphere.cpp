#include "Sphere.h"
#include <Graphics/DebugGraphics/DebugDrawer.h>

#include "AABB.h"

void dooms::physics::Sphere::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{

#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();
	debugGraphics->DebugDraw3DSphere(mCenter, mRadius, color);
#endif

}



dooms::physics::ColliderType dooms::physics::Sphere::GetColliderType() const
{
	return dooms::physics::ColliderType::Sphere;
}

