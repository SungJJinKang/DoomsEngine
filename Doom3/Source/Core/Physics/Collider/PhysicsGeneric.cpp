#include "PhysicsGeneric.h"

#include "AABB.h"
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Circle2D.h"


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



float doom::physics::DistanceFromPointToPlane(const math::Vector3& point, const Plane& plane)
{
	return math::dot(plane.GetNormal(), point) - plane.mDistance;
}

bool doom::physics::IsOverlapPointAndPlane(const math::Vector3& point, const Plane& plane)
{
	return math::abs(DistanceFromPointToPlane(point, plane)) < math::epsilon<float>();
}

bool doom::physics::IsOverlapRayAndSphere(const Ray& ray, const Sphere& sphere)
{
	math::Vector3 fromRayToSphere = sphere.mCenter - ray.mOrigin;
	float a = math::dot(fromRayToSphere, ray.GetNormal());

	// No collision
	if (sphere.mRadius * sphere.mRadius - fromRayToSphere.sqrMagnitude() + a * a < 0.0f) {
		return false;
	}
	else
	{
		return true;
	}
}

bool doom::physics::IsOverlapAABB3DAndPlane(Collider* aabb, Collider* plane)
{
	return IsOverlapAABB3DAndPlane(*static_cast<AABB3D*>(aabb), *static_cast<Plane*>(plane));
}

float doom::physics::RaycastRayAndAABB3D(const Ray& ray, const AABB3D& aabb) 
{
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

bool doom::physics::IsOverlapRayAndAABB3D(const Ray& ray, const AABB3D& aabb3d)
{
	/// reference : https://web.archive.org/web/20090803054252/http://tog.acm.org/resources/GraphicsGems/gems/RayBox.c


	static constexpr unsigned NUMDIM{ 3 };
	static constexpr unsigned RIGHT{ 0 };
	static constexpr unsigned LEFT{ 1 };
	static constexpr unsigned MIDDLE{ 2 };

	bool inside = true;
	unsigned int quadrant[NUMDIM];
	int whichPlane;
	float maxT[NUMDIM];
	float candidatePlane[NUMDIM];

	math::Vector3 hitPoint{};

	math::Vector3 normal{ ray.GetNormal() };

	/* Find candidate planes; this loop can be avoided if
	rays cast all from the eye(assume perpsective view) */
	for (unsigned int i = 0; i < NUMDIM; i++)
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
	for (unsigned int i = 0; i < NUMDIM; i++)
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
	for (unsigned int i = 1; i < NUMDIM; i++)
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
	for (unsigned int i = 0; i < NUMDIM; i++)
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

bool doom::physics::RaycastRayAndAABB3D(Collider * rayCollider, Collider * aabbCollider)
{

	Ray& ray{ *static_cast<Ray*>(rayCollider) };
	AABB3D& aabb{ *static_cast<AABB3D*>(aabbCollider) };
	return IsOverlapRayAndAABB3D(ray, aabb);
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

float doom::physics::RaycastLineAndAABB3D(const Line& line, const AABB3D& aabb)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndAABB3D(static_cast<Ray>(line), aabb)) ;
}

bool doom::physics::RaycastLineAndAABB3D(Collider* line, Collider* aabb)
{
	return RaycastLineAndAABB3D(*static_cast<Line*>(line), *static_cast<AABB3D*>(aabb)) > 0;
}

float doom::physics::RaycastLineAndSphere(const Line& line, const Sphere& sphere)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndSphere(static_cast<Ray>(line), sphere)) ;
}

bool doom::physics::RaycastLineAndSphere(Collider* line, Collider* sphere)
{
	return RaycastLineAndSphere(*static_cast<Line*>(line), *static_cast<Sphere*>(sphere)) > 0;
}

float doom::physics::RaycastLineAndPlane(const Line& line, const Plane& plane)
{
	return CheckLenghIsShorterThanLine(line, RaycastRayAndPlane(static_cast<Ray>(line), plane));
}

bool doom::physics::RaycastLineAndPlane(Collider* line, Collider* plane)
{
	return RaycastLineAndPlane(*static_cast<Line*>(line), *static_cast<Plane*>(plane)) > 0;
}

float doom::physics::RaycastRayAndAABB2D(const Ray& ray, const AABB2D& aabb)
{
	return 0.0f;
}

float doom::physics::RaycastRayAndCirecle2D(const Ray& ray, const Circle2D& circle2d)
{
	return 0.0f;
}

bool doom::physics::IsOverlapRayAndAABB2D(const Ray& ray, const AABB2D& aabb2d)
{
	return ray.mOrigin.x > aabb2d.mLowerBound.x && ray.mOrigin.y > aabb2d.mLowerBound.y
		&& ray.mOrigin.x < aabb2d.mUpperBound.x&& ray.mOrigin.y < aabb2d.mUpperBound.x;
}

bool doom::physics::RaycastRayAndAABB2D(Collider* rayCollider, Collider* aabbCollider)
{
	Ray& ray = *static_cast<Ray*>(rayCollider);
	AABB2D& aabb2d = *static_cast<AABB2D*>(aabbCollider);
	return IsOverlapRayAndAABB2D(ray, aabb2d);
}

bool doom::physics::RaycastRayAndCirecle2D(Collider* rayCollider, Collider* circle2dCollider)
{
	Ray& ray = *static_cast<Ray*>(rayCollider);
	Circle2D& circle2d = *static_cast<Circle2D*>(circle2dCollider);
	
	math::Vector2 dir{ ray.mOrigin.x - circle2d.mCenter.x, ray.mOrigin.y - circle2d.mCenter.y };
	float distanceSqr{ dir.sqrMagnitude() };
	return distanceSqr < circle2d.mRadius * circle2d.mRadius;
}

float doom::physics::RaycastLineAndAABB2D(const Line& line, const AABB2D& aabb)
{
	return 0.0f;
}

float doom::physics::RaycastLineAndCirecle2D(const Line& line, const Circle2D& circle2d)
{
	return 0.0f;
}

bool doom::physics::RaycastLineAndAABB2D(Collider* lineCollider, Collider* aabbCollider)
{
	Line& line = *static_cast<Line*>(lineCollider);
	AABB2D& aabb2d = *static_cast<AABB2D*>(aabbCollider);

	return line.mOrigin.x > aabb2d.mLowerBound.x && line.mOrigin.y > aabb2d.mLowerBound.y
		&& line.mOrigin.x < aabb2d.mUpperBound.x&& line.mOrigin.y < aabb2d.mUpperBound.x;
}

bool doom::physics::RaycastLineAndCirecle2D(Collider* lineCollider, Collider* circle2dCollider)
{
	Line& line = *static_cast<Line*>(lineCollider);
	Circle2D& circle2d = *static_cast<Circle2D*>(circle2dCollider);

	math::Vector2 dir{ line.mOrigin.x - circle2d.mCenter.x, line.mOrigin.y - circle2d.mCenter.y };
	float distanceSqr{ dir.sqrMagnitude() };
	return distanceSqr < circle2d.mRadius* circle2d.mRadius;
}

////////////////////////////////////////////////////////////////////////////////
//2D

