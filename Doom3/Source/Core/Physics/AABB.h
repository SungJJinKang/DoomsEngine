#pragma once
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
namespace doom
{
	namespace physics
	{
		struct Ray
		{
			math::Vector3 mPosition;
			math::Vector3 mNormal;
		};

		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		struct AABB3D 
		{
			math::Vector3 mLowerBound; // minimum extent
			math::Vector3 mUpperBound; // maximum extent

			AABB3D(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{

			}
		};

		struct AABB2D 
		{
			math::Vector2 mLowerBound; // minimum extent
			math::Vector2 mUpperBound; // maximum extent

			AABB2D(const math::Vector2& lowerBound, const math::Vector2& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{

			}
		};

		AABB2D Union(const AABB2D& A, const AABB2D& B)
		{
			return AABB2D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
		}

		AABB3D Union(const AABB3D& A, const AABB3D& B)
		{
			return AABB3D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
		}

		/// <summary>
		/// ºÎÇÇ
		/// </summary>
		/// <param name="A"></param>
		/// <returns></returns>
		float Area(const AABB3D& A)
		{
			math::Vector3 d = A.mUpperBound - A.mLowerBound;
			return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
		}
		float Area(const AABB2D& A)
		{
			math::Vector2 d = A.mUpperBound - A.mLowerBound;
			return d.x * d.y;
		}

		bool IsOverlap(const AABB2D& A, const math::Vector2& Point)
		{
			return (Point.x >= A.mLowerBound.x && Point.x <= A.mUpperBound.x) &&
				(Point.y >= A.mLowerBound.y && Point.y <= A.mUpperBound.y);
		}

		bool IsOverlap(const AABB2D& A, const AABB2D& B)
		{
			return A.mUpperBound.x > B.mLowerBound.x && A.mLowerBound.x < B.mUpperBound.x &&
				A.mUpperBound.y  > B.mLowerBound.y && A.mLowerBound.y < B.mUpperBound.y;
		}

		bool IsOverlap(const AABB3D& A, const math::Vector3& Point)
		{
			return (Point.x >= A.mLowerBound.x && Point.x <= A.mUpperBound.x) &&
				(Point.y >= A.mLowerBound.y && Point.y <= A.mUpperBound.y) &&
				(Point.z >= A.mLowerBound.z && Point.z <= A.mUpperBound.z);
		}

		bool IsOverlap(const AABB3D& A, const AABB3D& B)
		{
			return (A.mLowerBound.x <= B.mUpperBound.x && A.mUpperBound.x >= B.mLowerBound.x) &&
				(A.mLowerBound.y <= B.mUpperBound.y && A.mUpperBound.y >= B.mLowerBound.y) &&
				(A.mLowerBound.z <= B.mUpperBound.z && A.mUpperBound.z >= B.mLowerBound.z);
		}

		float Raycast(Ray ray, AABB3D aabb) {
			float t1 = (aabb.mLowerBound.x - ray.mPosition.x) / ray.mNormal.x;
			float t2 = (aabb.mUpperBound.x - ray.mPosition.x) / ray.mNormal.x;
			float t3 = (aabb.mLowerBound.y - ray.mPosition.y) / ray.mNormal.y;
			float t4 = (aabb.mUpperBound.y - ray.mPosition.y) / ray.mNormal.y;
			float t5 = (aabb.mLowerBound.z - ray.mPosition.z) / ray.mNormal.z;
			float t6 = (aabb.mUpperBound.z - ray.mPosition.z) / ray.mNormal.z;

			float tmin = math::max(math::max(math::min(t1, t2), math::min(t3, t4)), math::min(t5, t6));
			float tmax = math::min(math::min(math::max(t1, t2), math::max(t3, t4)), math::max(t5, t6));

			// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
			if (tmax < 0) {
				return -1;
			}

			// if tmin > tmax, ray doesn't intersect AABB
			if (tmin > tmax) {
				return -1;
			}

			if (tmin < 0.0f) {
				return tmax;
			}
			return tmin;
		}
	}
}

