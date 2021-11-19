#include "PhysicsGeneric.h"

#include "AABB.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Circle2D.h"


bool dooms::physics::IsOverlapSphereAndAABB3D(const Sphere& sphere, const AABB3D& aabb)
{
	return (GetClosestPointOnAABB(sphere, aabb) - sphere.mCenter).sqrMagnitude() < sphere.mRadius * sphere.mRadius;
}

bool dooms::physics::IsOverlapSphereAndAABB3D(const Collider* const sphere, const Collider* const aabb)
{
	return IsOverlapSphereAndAABB3D(*static_cast<const Sphere*>(sphere), *static_cast<const AABB3D*>(aabb));
}

math::Vector3 dooms::physics::GetClosestPointOnAABB(const Sphere& sphere, const AABB3D& aabb)
{
	math::Vector3 closestPoint{ nullptr };
	closestPoint.x = math::Min(math::Max(sphere.mCenter.x, aabb.mLowerBound.x), aabb.mUpperBound.x);
	closestPoint.y = math::Min(math::Max(sphere.mCenter.y, aabb.mLowerBound.y), aabb.mUpperBound.y);
	closestPoint.z = math::Min(math::Max(sphere.mCenter.z, aabb.mLowerBound.z), aabb.mUpperBound.z);

	return closestPoint;
}

bool dooms::physics::IsOverlapSphereAndPlane(const Sphere& sphere, const Plane& plane)
{
	return DistanceFromSphereToPlane(sphere, plane) < sphere.mRadius;
}

bool dooms::physics::IsOverlapSphereAndPlane(const Collider* const sphere, const Collider* const plane)
{
	return IsOverlapSphereAndPlane(*static_cast<const Sphere*>(sphere), *static_cast<const Plane*>(plane));
}

FLOAT32 dooms::physics::DistanceFromSphereToPlane(const Sphere& sphere, const Plane& plane)
{
	return math::dot(sphere.mCenter, plane.GetNormal()) - plane.mDistance;
}

math::Vector3 dooms::physics::GetClosestPointOnPlane(const Sphere& sphere, const Plane& plane)
{
	return sphere.mCenter - plane.GetNormal() * DistanceFromSphereToPlane(sphere, plane);
}

FLOAT32 dooms::physics::DistanceFromAABBToPlane(const AABB3D& aabb, const Plane& plane)
{
	const math::Vector3 centerOfAABB = math::Vector3{ (aabb.mLowerBound + aabb.mUpperBound) * 0.5f };
	return math::dot(plane.GetNormal(), centerOfAABB) - plane.mDistance;
}

bool dooms::physics::IsOverlapAABB3DAndPlane(const AABB3D& aabb, const Plane& plane)
{
	const math::Vector3 positiveExtent = static_cast<math::Vector3>(aabb.GetHalfExtent());
	 
	const math::Vector3 normalOfPlane = plane.GetNormal();
	FLOAT32 r = positiveExtent.x * std::abs(normalOfPlane.x)
		+ positiveExtent.y * std::abs(normalOfPlane.y)
		+ positiveExtent.z * std::abs(normalOfPlane.z);

	FLOAT32 s = DistanceFromAABBToPlane(aabb, plane);
	return std::abs(s) <= r;
}



FLOAT32 dooms::physics::DistanceFromPointToPlane(const math::Vector3& point, const Plane& plane)
{
	return math::dot(plane.GetNormal(), point) - plane.mDistance;
}

bool dooms::physics::IsOverlapPointAndPlane(const math::Vector3& point, const Plane& plane)
{
	return std::abs(DistanceFromPointToPlane(point, plane)) < math::epsilon_FLOAT32();
}

bool dooms::physics::IsOverlapRayAndSphere(const Ray& ray, const Sphere& sphere)
{
	math::Vector3 fromRayToSphere = sphere.mCenter - ray.mOrigin;
	FLOAT32 a = math::dot(fromRayToSphere, ray.GetNormal());

	// No collision
	if (sphere.mRadius * sphere.mRadius - fromRayToSphere.sqrMagnitude() + a * a < 0.0f) {
		return false;
	}
	else
	{
		return true;
	}
}

bool dooms::physics::IsOverlapAABB3DAndPlane(const Collider* const aabb, const Collider* const plane)
{
	return IsOverlapAABB3DAndPlane(*static_cast<const AABB3D*>(aabb), *static_cast<const Plane*>(plane));
}

FLOAT32 dooms::physics::RaycastRayAndAABB3D(const Ray& ray, const AABB3D& aabb) 
{
	auto normal = ray.GetNormal();

	FLOAT32 t1 = (aabb.mLowerBound.x - ray.mOrigin.x) / normal.x;
	FLOAT32 t2 = (aabb.mUpperBound.x - ray.mOrigin.x) / normal.x;
	FLOAT32 t3 = (aabb.mLowerBound.y - ray.mOrigin.y) / normal.y;
	FLOAT32 t4 = (aabb.mUpperBound.y - ray.mOrigin.y) / normal.y;
	FLOAT32 t5 = (aabb.mLowerBound.z - ray.mOrigin.z) / normal.z;
	FLOAT32 t6 = (aabb.mUpperBound.z - ray.mOrigin.z) / normal.z;

	FLOAT32 tMin = math::Max(math::Max(math::Min(t1, t2), math::Min(t3, t4)), math::Min(t5, t6));
	FLOAT32 tMax = math::Min(math::Min(math::Max(t1, t2), math::Max(t3, t4)), math::Max(t5, t6));

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

bool dooms::physics::IsOverlapRayAndAABB3D(const Ray& ray, const AABB3D& aabb3d)
{
	/// reference : https://web.archive.org/web/20090803054252/http://tog.acm.org/resources/GraphicsGems/gems/RayBox.c


	static constexpr unsigned NUMDIM{ 3 };
	static constexpr unsigned RIGHT{ 0 };
	static constexpr unsigned LEFT{ 1 };
	static constexpr unsigned MIDDLE{ 2 };

	bool inside = true;
	UINT32 quadrant[NUMDIM];
	INT32 whichPlane;
	FLOAT32 maxT[NUMDIM];
	FLOAT32 candidatePlane[NUMDIM];

	math::Vector3 hitPoint{ nullptr };

	math::Vector3 normal{ ray.GetNormal() };

	/* Find candidate planes; this loop can be avoided if
	rays cast all from the eye(assume perpsective view) */
	for (UINT32 i = 0; i < NUMDIM; i++)
	{
		if (ray.mOrigin[i] < aabb3d.mLowerBound[i])
		{
			quadrant[i] = LEFT;
			candidatePlane[i] = aabb3d.mLowerBound[i];
			inside = false;
		}
		else if (ray.mOrigin[i] > aabb3d.mUpperBound[i])
		{
			quadrant[i] = RIGHT;
			candidatePlane[i] = aabb3d.mUpperBound[i];
			inside = false;
		}
		else {
			quadrant[i] = MIDDLE;
		}
	}

	/* Ray origin inside bounding box */
	if (inside) {
		hitPoint = ray.mOrigin;
		return true;
	}


	/* Calculate T distances to candidate planes */
	for (UINT32 i = 0; i < NUMDIM; i++)
	{
		if (quadrant[i] != MIDDLE && normal[i] != 0.)
		{
			maxT[i] = (candidatePlane[i] - ray.mOrigin[i]) / normal[i];
		}
		else
		{
			maxT[i] = -1.0f;
		}
	}

	/* Get largest of the maxT's for final choice of intersection */
	whichPlane = 0;
	for (UINT32 i = 1; i < NUMDIM; i++)
	{
		if (maxT[whichPlane] < maxT[i])
		{
			whichPlane = i;
		}
	}

	/* Check final candidate actually inside box */
	if (maxT[whichPlane] < 0.)
	{
		return false;
	}
	for (UINT32 i = 0; i < NUMDIM; i++)
	{
		if (whichPlane != i)
		{
			hitPoint[i] = ray.mOrigin[i] + maxT[whichPlane] * normal[i];
			if (hitPoint[i] < aabb3d.mLowerBound[i] || hitPoint[i] > aabb3d.mUpperBound[i])
			{
				return false;
			}
		}
		else {
			hitPoint[i] = candidatePlane[i];
		}
	}

	return true;
}

bool dooms::physics::RaycastRayAndAABB3D(const Collider* const rayCollider, const Collider* const aabbCollider)
{

	const Ray& ray{ *static_cast<const Ray*>(rayCollider) };
	const AABB3D& aabb{ *static_cast<const AABB3D*>(aabbCollider) };
	return IsOverlapRayAndAABB3D(ray, aabb);
}

/// <summary>
/// see this : https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_sphere.html
/// </summary>
/// <param name="ray"></param>
/// <param name="sphere"></param>
/// <returns></returns>
FLOAT32 dooms::physics::RaycastRayAndSphere(const Ray& ray, const Sphere& sphere)
{
	math::Vector3 fromRayToSphere = sphere.mCenter - ray.mOrigin;
	FLOAT32 e = fromRayToSphere.magnitude();
	FLOAT32 a = math::dot(fromRayToSphere, ray.GetNormal());
	FLOAT32 b = std::sqrt(e * e - a * a);
	FLOAT32 f = std::sqrt(sphere.mRadius * sphere.mRadius - b * b);
	//FLOAT32 t = a - f;

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

bool dooms::physics::RaycastRayAndSphere(const Collider* const ray, const Collider* const sphere)
{
	return RaycastRayAndSphere(*static_cast<const Ray*>(ray), *static_cast<const Sphere*>(sphere)) > 0;
}

FLOAT32 dooms::physics::RaycastRayAndPlane(const Ray& ray, const Plane& plane)
{
	FLOAT32 denom = math::dot(ray.GetNormal(), plane.GetNormal());
	if (std::abs(denom) > math::epsilon_FLOAT32())
	{
		math::Vector3 p0l0 = plane.GetNormal() * plane.mDistance - ray.mOrigin;
		FLOAT32 t = math::dot(p0l0, plane.GetNormal()) / denom;
		return t;
	}
	else
	{// when ray and normal parallel
		return -1;
	}
}

bool dooms::physics::RaycastRayAndPlane(const Collider* const ray, const Collider* const plane)
{
	return RaycastRayAndPlane(*static_cast<const Ray*>(ray), *static_cast<const Plane*>(plane)) > 0;
}



FLOAT32 dooms::physics::CheckLenghIsShorterThanLine(const Line& line, FLOAT32 length)
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

FLOAT32 dooms::physics::RaycastLineAndAABB3D(const Line& line, const AABB3D& aabb)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndAABB3D(static_cast<Ray>(line), aabb)) ;
}

bool dooms::physics::RaycastLineAndAABB3D(const Collider* const line, const Collider* const aabb)
{
	return RaycastLineAndAABB3D(*static_cast<const Line*>(line), *static_cast<const AABB3D*>(aabb)) > 0;
}

FLOAT32 dooms::physics::RaycastLineAndSphere(const Line& line, const Sphere& sphere)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndSphere(static_cast<Ray>(line), sphere)) ;
}

bool dooms::physics::RaycastLineAndSphere(const Collider* const line, const Collider* const sphere)
{
	return RaycastLineAndSphere(*static_cast<const Line*>(line), *static_cast<const Sphere*>(sphere)) > 0;
}

FLOAT32 dooms::physics::RaycastLineAndPlane(const Line& line, const Plane& plane)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndPlane(static_cast<Ray>(line), plane));
}

bool dooms::physics::RaycastLineAndPlane(const Collider* const line, const Collider* const plane)
{
	return RaycastLineAndPlane(*static_cast<const Line*>(line), *static_cast<const Plane*>(plane)) > 0;
}

FLOAT32 dooms::physics::RaycastRayAndAABB2D(const Ray& ray, const AABB2D& aabb)
{
	return 0.0f;
}

FLOAT32 dooms::physics::RaycastRayAndCirecle2D(const Ray& ray, const Circle2D& circle2d)
{
	return 0.0f;
}

bool dooms::physics::IsOverlapRayAndAABB2D(const Ray& ray, const AABB2D& aabb2d)
{
	return ray.mOrigin.x > aabb2d.mLowerBound.x && ray.mOrigin.y > aabb2d.mLowerBound.y
		&& ray.mOrigin.x < aabb2d.mUpperBound.x&& ray.mOrigin.y < aabb2d.mUpperBound.x;
}

bool dooms::physics::RaycastRayAndAABB2D(const Collider* const rayCollider, const Collider* const aabbCollider)
{
	const Ray& ray = *static_cast<const Ray*>(rayCollider);
	const AABB2D& aabb2d = *static_cast<const AABB2D*>(aabbCollider);
	return IsOverlapRayAndAABB2D(ray, aabb2d);
}

bool dooms::physics::RaycastRayAndCirecle2D(const Collider* const rayCollider, const Collider* const circle2dCollider)
{
	const Ray& ray = *static_cast<const Ray*>(rayCollider);
	const Circle2D& circle2d = *static_cast<const Circle2D*>(circle2dCollider);
	
	math::Vector2 dir{ ray.mOrigin.x - circle2d.mCenter.x, ray.mOrigin.y - circle2d.mCenter.y };
	FLOAT32 distanceSqr{ dir.sqrMagnitude() };
	return distanceSqr < circle2d.mRadius * circle2d.mRadius;
}

FLOAT32 dooms::physics::RaycastLineAndAABB2D(const Line& line, const AABB2D& aabb)
{
	return 0.0f;
}

FLOAT32 dooms::physics::RaycastLineAndCirecle2D(const Line& line, const Circle2D& circle2d)
{
	return 0.0f;
}

bool dooms::physics::RaycastLineAndAABB2D(const Collider* const lineCollider, const Collider* const aabbCollider)
{
	const Line& line = *static_cast<const Line*>(lineCollider);
	const AABB2D& aabb2d = *static_cast<const AABB2D*>(aabbCollider);

	return line.mOrigin.x > aabb2d.mLowerBound.x && line.mOrigin.y > aabb2d.mLowerBound.y
		&& line.mOrigin.x < aabb2d.mUpperBound.x&& line.mOrigin.y < aabb2d.mUpperBound.x;
}

bool dooms::physics::RaycastLineAndCirecle2D(const Collider* const lineCollider, const Collider* const circle2dCollider)
{
	const Line& line = *static_cast<const Line*>(lineCollider);
	const Circle2D& circle2d = *static_cast<const Circle2D*>(circle2dCollider);

	math::Vector2 dir{ line.mOrigin.x - circle2d.mCenter.x, line.mOrigin.y - circle2d.mCenter.y };
	FLOAT32 distanceSqr{ dir.sqrMagnitude() };
	return distanceSqr < circle2d.mRadius* circle2d.mRadius;
}

////////////////////////////////////////////////////////////////////////////////
//2D

