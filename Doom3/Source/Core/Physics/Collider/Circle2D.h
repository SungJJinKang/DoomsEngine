#pragma once
#include "../Core.h"
#include <Vector2.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class Circle2D : public Collider
		{
		private:
		
		protected:
			void Render(eColor color) override;

		public:
			Circle2D(const math::Vector2& center, float radius);

			math::Vector2 mCenter;
			float mRadius;

			ColliderType GetColliderType() const override;

		};

	

	}
}

