#pragma once

#include <Vector3.h>

namespace doom
{
	namespace physics
	{
		class Collider;
		class AABB2D;
		class AABB3D;
		class Circle2D;
		class Line;
		class Plane;
		class Ray;
		class Sphere;

		bool IsOverlapSphereAndAABB3D(const Sphere& sphere, const AABB3D& aabb);
		bool IsOverlapSphereAndAABB3D(Collider* sphere, Collider* aabb);
		math::Vector3 GetClosestPointOnAABB(const Sphere& sphere, const AABB3D& aabb);

		bool IsOverlapSphereAndPlane(const Sphere& sphere, const Plane& plane);
		bool IsOverlapSphereAndPlane(Collider* sphere, Collider* plane);
		float DistanceFromSphereToPlane(const Sphere& sphere, const Plane& plane);
		math::Vector3 GetClosestPointOnPlane(const Sphere& sphere, const Plane& plane);

		float DistanceFromAABBToPlane(const AABB3D& aabb, const Plane& plane);
		bool IsOverlapAABB3DAndPlane(const AABB3D& aabb, const Plane& plane);
		bool IsOverlapAABB3DAndPlane(Collider* aabb, Collider* plane);

		/// <summary>
		/// if return positive value, point is on normal side of plane,
		/// otherwise
		/// </summary>
		/// <param name="point"></param>
		/// <param name="plane"></param>
		/// <returns></returns>
		float DistanceFromPointToPlane(const math::Vector3& point, const Plane& plane);
		bool IsOverlapPointAndPlane(const math::Vector3& point, const Plane& plane);
		bool IsOverlapRayAndSphere(const Ray& ray, const Sphere& sphere);

		float RaycastRayAndAABB3D(const Ray& rayCollider, const AABB3D& aabbCollider);
		float RaycastRayAndSphere(const Ray& ray, const Sphere& sphere);
		float RaycastRayAndPlane(const Ray& ray, const Plane& plane); 
		bool RaycastRayAndAABB3D(Collider * rayCollider, Collider * aabbCollider);
		bool RaycastRayAndSphere(Collider* ray, Collider* sphere);
		bool RaycastRayAndPlane(Collider* ray, Collider* plane);

		bool IsOverlapRayAndAABB3D(const Ray& ray, const AABB3D& aabb);

		/// <summary>
		/// return lenght if line's length is larger than argumnet length
		/// if not, return -1
		/// </summary>
		/// <param name="line"></param>
		/// <param name="length"></param>
		/// <returns></returns>
		float CheckLenghIsShorterThanLine(const Line& line, float length);
		float RaycastLineAndAABB3D(const Line& line, const AABB3D& aabb3d);
		float RaycastLineAndSphere(const Line& line, const Sphere& sphere);
		float RaycastLineAndPlane(const Line& line, const Plane& plane);
		bool RaycastLineAndAABB3D(Collider* line, Collider* aabb);
		bool RaycastLineAndSphere(Collider* line, Collider* sphere);
		bool RaycastLineAndPlane(Collider* line, Collider* plane);


		//
		// 2D

		float RaycastRayAndAABB2D(const Ray& ray, const AABB2D& aabb);
		float RaycastRayAndCirecle2D(const Ray& ray, const Circle2D& circle2d);

		bool IsOverlapRayAndAABB2D(const Ray& ray, const AABB2D& aabb2d);
		bool RaycastRayAndAABB2D(Collider* rayCollider, Collider* aabbCollider);
		bool RaycastRayAndCirecle2D(Collider* rayCollider, Collider* circle2dCollider);

		float RaycastLineAndAABB2D(const Line& line, const AABB2D& aabb);
		float RaycastLineAndCirecle2D(const Line& line, const Circle2D& circle2d);
		bool RaycastLineAndAABB2D(Collider* lineCollider, Collider* aabbCollider);
		bool RaycastLineAndCirecle2D(Collider* lineCollider, Collider* circle2dCollider);

	}
}
