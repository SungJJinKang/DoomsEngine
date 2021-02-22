#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "IRenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Ray : public IRenderPhysics
		{
		private:
			math::Vector3 mNormal;

		protected:
			virtual void _DebugRender() final;

		public:
			math::Vector3 mPosition;

			Ray(const math::Vector3& pos, const math::Vector3& normal);
			math::Vector3 GetNormal() const;
				
			bool IsPointOnRay(const math::Vector3& point);
			static math::Vector3 GetClosestPoint(const Ray& ray, const math::Vector3& point);
		};
	}
}