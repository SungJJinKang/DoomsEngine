#pragma once
#include "../Core.h"
#include <Vector2.h>
#include "IRenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Circle2D : public IRenderPhysics
		{
		private:
		
		protected:
			void _DebugRender() override;

		public:
			math::Vector2 mCenter;
			float mRadius;
		};
	}
}

