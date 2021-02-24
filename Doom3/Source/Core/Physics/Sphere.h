#pragma once


#include "../Core.h"
#include <Vector3.h>
#include "RenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Sphere : public RenderPhysics
		{
		private:
			

			// Inherited via RenderPhysics
			virtual void Render(eColor color) final;

		public:
			Sphere(const math::Vector3& center, float radius);
			math::Vector3 mCenter;
			float mRadius;

			
		};

		bool IsOverlap(const Sphere& sphere1, const Sphere& sphere2);
	}
}

