#pragma once

#include "../Core.h"
#include <Vector3.h>
namespace doom
{
	namespace physics
	{
		class Ray
		{
		private:
			math::Vector3 mNormal;

		public:
			math::Vector3 mPosition;

			Ray(const math::Vector3& pos, const math::Vector3& normal);
			math::Vector3 GetNormal() const;
				
			bool IsPointOnRay(const math::Vector3& point);
			static math::Vector3 GetClosestPoint(const Ray& ray, const math::Vector3& point);
		};
	}
}