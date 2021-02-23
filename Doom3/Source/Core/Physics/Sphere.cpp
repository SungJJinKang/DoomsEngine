#include "Sphere.h"

void doom::physics::Sphere::_DebugRender()
{
}



bool doom::physics::IsOverlap(const Sphere& sphere1, const Sphere& sphere2)
{
	return (sphere1.mCenter - sphere2.mCenter).sqrMagnitude() < math::pow(sphere1.mRadius + sphere2.mRadius, 2);
}
