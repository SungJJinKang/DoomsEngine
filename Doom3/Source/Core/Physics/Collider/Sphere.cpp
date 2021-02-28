#include "Sphere.h"
#include "../Graphics/DebugGraphics.h"
void doom::physics::Sphere::Render(eColor color)
{
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	const float intervalRadian = math::PI * 2 / 72.0f;

	// TODO: MAKE THIS LATER
	// https://github.com/caosdoar/spheres
}

doom::physics::Sphere::Sphere(const math::Vector3& center, float radius)
	:mCenter{ center }, mRadius{ radius }
{
}



doom::physics::ColliderType doom::physics::Sphere::GetColliderType() const
{
	return doom::physics::ColliderType::Sphere;
}

bool doom::physics::IsOverlapSphereAndSphere(const Sphere& sphere1, const Sphere& sphere2)
{
	return (sphere1.mCenter - sphere2.mCenter).sqrMagnitude() < math::pow(sphere1.mRadius + sphere2.mRadius, 2);
}

bool doom::physics::IsOverlapSphereAndSphere(Collider* sphere1, Collider* sphere2)
{
	return IsOverlapSphereAndSphere(*static_cast<Sphere*>(sphere1), *static_cast<Sphere*>(sphere2));
}
