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
			void Render(eColor color, bool drawInstantly = false) override;

		public:
			Circle2D(const math::Vector2& center, float radius);

			math::Vector2 mCenter;
			float mRadius;

			FORCE_INLINE virtual void* data() final
			{
				return &(this->mCenter);
			}

			ColliderType GetColliderType() const override;

		};

		bool IsOverlapCircle2DAndCircle2D(const Circle2D& circle2d1, const Circle2D& circle2d2);
		bool IsOverlapCircle2DAndCircle2D(Collider* circle2d1, Collider* circle2d2);
	}
}

