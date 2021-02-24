#pragma once
#include "../Core.h"
#include <Vector2.h>
#include "RenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Circle2D : public RenderPhysics
		{
		private:
		
		protected:
			void Render(eColor color) override;

		public:
			Circle2D(const math::Vector2& center, float radius);

			math::Vector2 mCenter;
			float mRadius;
		};
	}
}

