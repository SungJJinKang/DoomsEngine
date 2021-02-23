#pragma once

#include <Vector3.h>

namespace doom
{
	namespace physics
	{
		class AABB2D;
		class AABB3D;
		class Line;
		class Plane;
		class Ray;
		class Sphere;

		bool IsOverlap(const Sphere& sphere, const AABB3D& aabb);
		math::Vector3 GetClosestPointOnAABB(const Sphere& sphere, const AABB3D& aabb);

		bool IsOverlap(const Sphere& sphere, const Plane& plane);
		float DistanceFromSphereToPlane(const Sphere& sphere, const Plane& plane);
		math::Vector3 GetClosestPointOnPlane(const Sphere& sphere, const Plane& plane);

		float DistanceFromAABBToPlane(const AABB3D& aabb, const Plane& plane);
		bool IsOverlap(const AABB3D& aabb, const Plane& plane);



		bool Raycast(const Ray& ray, const AABB3D& aabb);
		bool Raycast(const Ray& ray, const Sphere& sphere);
		bool Raycast(const Ray& ray, const Plane& plane);

	}
}
