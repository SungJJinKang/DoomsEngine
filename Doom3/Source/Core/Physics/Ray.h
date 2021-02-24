#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "RenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Ray : public RenderPhysics
		{
		private:
			math::Vector3 mNormal;

		protected:
			virtual void Render(eColor color) override;

		public:
			math::Vector3 mOrigin;

			Ray(const math::Vector3 & origin, const math::Vector3& normal);
			math::Vector3 GetNormal() const;
				
			bool IsPointOnRay(const math::Vector3& point);
			static math::Vector3 GetClosestPoint(const Ray& ray, const math::Vector3& point);
		};
	}
}