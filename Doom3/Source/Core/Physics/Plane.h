#pragma once

#include "../Core.h"
#include <Vector3.h>
namespace doom
{
	namespace physics
	{
		class Plane
		{
		private:
			float mDistance;
			math::Vector3 mNormal;

		public:

			Plane(float distance, const math::Vector3& normal);
			Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C);

			float GetDistance() const;
			math::Vector3 GetNormal() const;
		};

		bool IsPointOnPlane(const Plane& plane, const math::Vector3& point);
		/// <summary>
		/// return if point is in front of plane ( is at half space where normal vector forward )
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		bool IsPointOnPositiveSide(const Plane& plane, const math::Vector3& point);
		/// <summary>
		/// Get Closest Point To Point
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		math::Vector3 GetClosestPoint(const Plane& plane, const math::Vector3& point);
	}
}

