#pragma once


#include "../Core.h"
#include <Vector3.h>
#include "IRenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Sphere : public IRenderPhysics
		{
		private:
			

			// Inherited via IRenderPhysics
			virtual void _DebugRender() final;

		public:
			math::Vector3 mCenter;
			float mRadius;

			
		};

		bool IsOverlap(const Sphere& sphere1, const Sphere& sphere2);
	}
}

