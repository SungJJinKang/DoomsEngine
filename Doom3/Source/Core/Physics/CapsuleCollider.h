#pragma once
#include "../Core.h"
#include <Vector3.h>
#include "RenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class CapsuleCollider : public RenderPhysics
		{

		public:

			math::Vector3 mCenter;
			float mHeight;
			float mRadius;
		};


	}
}