#include "PhysicsGeneric.h"

#include "AABB.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"


bool doom::physics::IsOverlap(const Sphere& sphere, const AABB3D& aabb)
{
	return (GetClosestPointOnAABB(sphere, aabb) - sphere.mCenter).sqrMagnitude() < sphere.mRadius * sphere.mRadius;
}

math::Vector3 doom::physics::GetClosestPointOnAABB(const Sphere& sphere, const AABB3D& aabb)
{
	math::Vector3 closestPoint{};
	closestPoint.x = math::min(math::max(sphere.mCenter.x, aabb.mLowerBound.x), aabb.mUpperBound.x);
	closestPoint.y = math::min(math::max(sphere.mCenter.y, aabb.mLowerBound.y), aabb.mUpperBound.y);
	closestPoint.z = math::min(math::max(sphere.mCenter.z, aabb.mLowerBound.z), aabb.mUpperBound.z);

	return closestPoint;
}

bool doom::physics::IsOverlap(const Sphere& sphere, const Plane& plane)
{
	return DistanceFromSphereToPlane(sphere, plane) < sphere.mRadius;
}

float doom::physics::DistanceFromSphereToPlane(const Sphere& sphere, const Plane& plane)
{
	return math::dot(sphere.mCenter, plane.GetNormal()) - plane.mDistance;
}

math::Vector3 doom::physics::GetClosestPointOnPlane(const Sphere& sphere, const Plane& plane)
{
	return sphere.mCenter - plane.GetNormal() * DistanceFromSphereToPlane(sphere, plane);
}

float doom::physics::DistanceFromAABBToPlane(const AABB3D& aabb, const Plane& plane)
{
	const math::Vector3 centerOfAABB = (aabb.mLowerBound + aabb.mUpperBound) * 0.5f;
	return math::dot(plane.GetNormal(), centerOfAABB) - plane.mDistance;
}

bool doom::physics::IsOverlap(const AABB3D& aabb, const Plane& plane)
{
	const math::Vector3 centerOfAABB = (aabb.mLowerBound + aabb.mUpperBound) * 0.5f;
	const math::Vector3 positiveExtent = aabb.mUpperBound - centerOfAABB;

	const math::Vector3 normalOfPlane = plane.GetNormal();
	float r = positiveExtent.x * math::abs(normalOfPlane.x)
		+ positiveExtent.y * math::abs(normalOfPlane.y)
		+ positiveExtent.z * math::abs(normalOfPlane.z);

	float s = DistanceFromAABBToPlane(aabb, plane);
	return math::abs(s) <= r;
}



bool doom::physics::Raycast(const Ray& ray, const AABB3D& aabb) {
	auto normal = ray.GetNormal();

	float t1 = (aabb.mLowerBound.x - ray.mPosition.x) / normal.x;
	float t2 = (aabb.mUpperBound.x - ray.mPosition.x) / normal.x;
	float t3 = (aabb.mLowerBound.y - ray.mPosition.y) / normal.y;
	float t4 = (aabb.mUpperBound.y - ray.mPosition.y) / normal.y;
	float t5 = (aabb.mLowerBound.z - ray.mPosition.z) / normal.z;
	float t6 = (aabb.mUpperBound.z - ray.mPosition.z) / normal.z;

	float tmin = math::max(math::max(math::min(t1, t2), math::min(t3, t4)), math::min(t5, t6));
	float tmax = math::min(math::min(math::max(t1, t2), math::max(t3, t4)), math::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	//if (tmin < 0.0f) {
	//	return true;
	//}
	return true;
}

/// <summary>
/// see this : https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_sphere.html
/// </summary>
/// <param name="ray"></param>
/// <param name="sphere"></param>
/// <returns></returns>
bool doom::physics::Raycast(const Ray& ray, const Sphere& sphere)
{
	math::Vector3 fromRayToSphere = sphere.mCenter - ray.mPosition;
	float e = fromRayToSphere.magnitude();
	float a = math::dot(fromRayToSphere, ray.GetNormal());
	float b = math::sqrt(e * e - a * a);
	float f = math::sqrt(sphere.mRadius * sphere.mRadius - b * b);
	float t = a - f;

	// No collision
	if (sphere.mRadius * sphere.mRadius - fromRayToSphere.sqrMagnitude() + a * a < 0.0f) {
		return false; // -1 is invalid.
	}
	// Ray is inside
	else if (fromRayToSphere.sqrMagnitude() < sphere.mRadius * sphere.mRadius) {
		return true; // Just reverse direction
	}
	// else Normal intersection
	return a - f;
}

bool doom::physics::Raycast(const Ray& ray, const Plane& plane)
{
	float denom = math::dot(ray.GetNormal(), plane.GetNormal());
	if (denom > math::epsilon<float>())
	{
		math::Vector3 p0l0 = plane.GetNormal() * plane.mDistance - ray.mPosition;
		float t = math::dot(p0l0, plane.GetNormal()) / denom;
		return (t >= 0);
	}
	else
	{
		return false;
	}
}
