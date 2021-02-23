#pragma once
#include "../Core.h"
#include <Vector3.h>
#include "IRenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class CapsuleCollider
		{

		public:

			math::Vector3 mCenter;
			float mHeight;
			float mRadius;
		};


	}
}