#include "PhysicsGeneric.h"

#include "AABB.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"


bool doom::physics::IsOverlapSphereAndAABB3D(const Sphere& sphere, const AABB3D& aabb)
{
	return (GetClosestPointOnAABB(sphere, aabb) - sphere.mCenter).sqrMagnitude() < sphere.mRadius * sphere.mRadius;
}

bool doom::physics::IsOverlapSphereAndAABB3D(Collider* sphere, Collider* aabb)
{
	return IsOverlapSphereAndAABB3D(*static_cast<Sphere*>(sphere), *static_cast<AABB3D*>(aabb));
}

math::Vector3 doom::physics::GetClosestPointOnAABB(const Sphere& sphere, const AABB3D& aabb)
{
	math::Vector3 closestPoint{};
	closestPoint.x = math::Min(math::Max(sphere.mCenter.x, aabb.mLowerBound.x), aabb.mUpperBound.x);
	closestPoint.y = math::Min(math::Max(sphere.mCenter.y, aabb.mLowerBound.y), aabb.mUpperBound.y);
	closestPoint.z = math::Min(math::Max(sphere.mCenter.z, aabb.mLowerBound.z), aabb.mUpperBound.z);

	return closestPoint;
}

bool doom::physics::IsOverlapSphereAndPlane(const Sphere& sphere, const Plane& plane)
{
	return DistanceFromSphereToPlane(sphere, plane) < sphere.mRadius;
}

bool doom::physics::IsOverlapSphereAndPlane(Collider* sphere, Collider* plane)
{
	return IsOverlapSphereAndPlane(*static_cast<Sphere*>(sphere), *static_cast<Plane*>(plane));
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

bool doom::physics::IsOverlapAABB3DAndPlane(const AABB3D& aabb, const Plane& plane)
{
	const math::Vector3 positiveExtent = aabb.GetHalfExtent();

	const math::Vector3 normalOfPlane = plane.GetNormal();
	float r = positiveExtent.x * math::abs(normalOfPlane.x)
		+ positiveExtent.y * math::abs(normalOfPlane.y)
		+ positiveExtent.z * math::abs(normalOfPlane.z);

	float s = DistanceFromAABBToPlane(aabb, plane);
	return math::abs(s) <= r;
}



bool doom::physics::IsOverlapAABB3DAndPlane(Collider* aabb, Collider* plane)
{
	return IsOverlapAABB3DAndPlane(*static_cast<AABB3D*>(aabb), *static_cast<Plane*>(plane));
}

float doom::physics::RaycastRayAndAABB3D(const Ray& ray, const AABB3D& aabb) {
	auto normal = ray.GetNormal();

	float t1 = (aabb.mLowerBound.x - ray.mOrigin.x) / normal.x;
	float t2 = (aabb.mUpperBound.x - ray.mOrigin.x) / normal.x;
	float t3 = (aabb.mLowerBound.y - ray.mOrigin.y) / normal.y;
	float t4 = (aabb.mUpperBound.y - ray.mOrigin.y) / normal.y;
	float t5 = (aabb.mLowerBound.z - ray.mOrigin.z) / normal.z;
	float t6 = (aabb.mUpperBound.z - ray.mOrigin.z) / normal.z;

	float tMin = math::Max(math::Max(math::Min(t1, t2), math::Min(t3, t4)), math::Min(t5, t6));
	float tMax = math::Min(math::Min(math::Max(t1, t2), math::Max(t3, t4)), math::Max(t5, t6));

	// if tMax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tMax < 0) {
		return -1;
	}

	// if tMin > tMax, ray doesn't intersect AABB
	if (tMin > tMax) {
		return -1;
	}

	if (tMin < 0.0f) {
		return tMax;
	}
	return tMin;
}

bool doom::physics::RaycastRayAndAABB3D(Collider* ray, Collider* aabb)
{
	return RaycastRayAndAABB3D(*static_cast<Ray*>(ray), *static_cast<AABB3D*>(aabb)) > 0;
}

/// <summary>
/// see this : https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_sphere.html
/// </summary>
/// <param name="ray"></param>
/// <param name="sphere"></param>
/// <returns></returns>
float doom::physics::RaycastRayAndSphere(const Ray& ray, const Sphere& sphere)
{
	math::Vector3 fromRayToSphere = sphere.mCenter - ray.mOrigin;
	float e = fromRayToSphere.magnitude();
	float a = math::dot(fromRayToSphere, ray.GetNormal());
	float b = math::sqrt(e * e - a * a);
	float f = math::sqrt(sphere.mRadius * sphere.mRadius - b * b);
	float t = a - f;

	// No collision
	if (sphere.mRadius * sphere.mRadius - fromRayToSphere.sqrMagnitude() + a * a < 0.0f) {
		return -1; // -1 is invalid.
	}
	// Ray is inside
	else if (fromRayToSphere.sqrMagnitude() < sphere.mRadius * sphere.mRadius) {
		return a + f; // Just reverse direction
	}
	// else Normal intersection
	return a - f;
}

bool doom::physics::RaycastRayAndSphere(Collider* ray, Collider* sphere)
{
	return RaycastRayAndSphere(*static_cast<Ray*>(ray), *static_cast<Sphere*>(sphere)) > 0;
}

float doom::physics::RaycastRayAndPlane(const Ray& ray, const Plane& plane)
{
	float denom = math::dot(ray.GetNormal(), plane.GetNormal());
	if (math::abs(denom) > math::epsilon<float>())
	{
		math::Vector3 p0l0 = plane.GetNormal() * plane.mDistance - ray.mOrigin;
		float t = math::dot(p0l0, plane.GetNormal()) / denom;
		return t;
	}
	else
	{// when ray and normal parallel
		return -1;
	}
}

bool doom::physics::RaycastRayAndPlane(Collider* ray, Collider* plane)
{
	return RaycastRayAndPlane(*static_cast<Ray*>(ray), *static_cast<Plane*>(plane)) > 0;
}

float doom::physics::CheckLenghIsShorterThanLine(const Line& line, float length)
{
	if (length < 0)
	{
		return length;
	}
	else if ((line.mEndPoint - line.mOrigin).sqrMagnitude() < length * length)
	{
		return length;
	}
	else
	{
		return -1;
	}
}

bool doom::physics::RaycastLineAndAABB3D(const Line& line, const AABB3D& aabb)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndAABB3D(static_cast<Ray>(line), aabb)) > 0;
}

bool doom::physics::RaycastLineAndAABB3D(Collider* line, Collider* aabb)
{
	return RaycastLineAndAABB3D(*static_cast<Line*>(line), *static_cast<AABB3D*>(aabb));
}

bool doom::physics::RaycastLineAndSphere(const Line& line, const Sphere& sphere)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndSphere(static_cast<Ray>(line), sphere)) > 0;
}

bool doom::physics::RaycastLineAndSphere(Collider* line, Collider* sphere)
{
	return RaycastLineAndSphere(*static_cast<Line*>(line), *static_cast<Sphere*>(sphere));
}

bool doom::physics::RaycastLineAndPlane(const Line& line, const Plane& plane)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndPlane(static_cast<Ray>(line), plane)) > 0;
}

bool doom::physics::RaycastLineAndPlane(Collider* line, Collider* plane)
{
	return RaycastLineAndPlane(*static_cast<Line*>(line), *static_cast<Plane*>(plane));
}