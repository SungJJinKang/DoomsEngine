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
		bool IsOverlapSphereAndAABB3D(const Collider* const sphere, const Collider* const aabb);
		math::Vector3 GetClosestPointOnAABB(const Sphere& sphere, const AABB3D& aabb);

		bool IsOverlapSphereAndPlane(const Sphere& sphere, const Plane& plane);
		bool IsOverlapSphereAndPlane(const Collider* const sphere, const Collider* const plane);
		float DistanceFromSphereToPlane(const Sphere& sphere, const Plane& plane);
		math::Vector3 GetClosestPointOnPlane(const Sphere& sphere, const Plane& plane);

		float DistanceFromAABBToPlane(const AABB3D& aabb, const Plane& plane);
		bool IsOverlapAABB3DAndPlane(const AABB3D& aabb, const Plane& plane);
		bool IsOverlapAABB3DAndPlane(const Collider* const aabb, const Collider* const plane);

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
		bool RaycastRayAndAABB3D(const Collider* const rayCollider, const Collider* const aabbCollider);
		bool RaycastRayAndSphere(const Collider* const ray, const Collider* const sphere);
		bool RaycastRayAndPlane(const Collider* const ray, const Collider* const plane);

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
		bool RaycastLineAndAABB3D(const Collider* const line, const Collider* const aabb);
		bool RaycastLineAndSphere(const Collider* const line, const Collider* const sphere);
		bool RaycastLineAndPlane(const Collider* const line, const Collider* const plane);


		//
		// 2D

		float RaycastRayAndAABB2D(const Ray& ray, const AABB2D& aabb);
		float RaycastRayAndCirecle2D(const Ray& ray, const Circle2D& circle2d);

		bool IsOverlapRayAndAABB2D(const Ray& ray, const AABB2D& aabb2d);
		bool RaycastRayAndAABB2D(const Collider* const rayCollider, const Collider* const aabbCollider);
		bool RaycastRayAndCirecle2D(const Collider* const rayCollider, const Collider* const circle2dCollider);

		float RaycastLineAndAABB2D(const Line& line, const AABB2D& aabb);
		float RaycastLineAndCirecle2D(const Line& line, const Circle2D& circle2d);
		bool RaycastLineAndAABB2D(const Collider* const lineCollider, const Collider* const aabbCollider);
		bool RaycastLineAndCirecle2D(const Collider* const lineCollider, const Collider* const circle2dCollider);

	}
}
