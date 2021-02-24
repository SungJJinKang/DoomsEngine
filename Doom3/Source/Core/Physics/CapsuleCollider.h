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

			CapsuleCollider(const math::Vector3& center, float height, float radius);
		protected:
			void Render(eColor color) override;

		};


	}
}