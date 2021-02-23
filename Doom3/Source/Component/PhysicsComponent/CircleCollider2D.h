#pragma once
#include "Collider2D.h"
#include <Vector2.h>
#include <Circle2D.h>
namespace doom
{
	class CircleCollider2D : public Collider2D
	{
	private:

		physics::Circle2D mCircle2D;

		float mRadius;

		void UpdateCorePhysicsVariable() override;
		virtual void _UpdatePhysics() final;

	public:
	

		void SetRadius(float radius);
		float GetRadius();
	};
}
