#pragma once


#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class Sphere : public Collider
		{
		private:
			

			// Inherited via RenderPhysics
			virtual void Render(eColor color) final;

		public:
			Sphere(const math::Vector3& center, float radius);
			math::Vector3 mCenter;
			float mRadius;

			

			ColliderType GetColliderType() const override;

		};

		bool IsOverlap(const Sphere& sphere1, const Sphere& sphere2);
	}
}

