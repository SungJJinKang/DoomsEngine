#pragma once
#include "Collider2DComponent.h"
#include <Vector2.h>
#include <Collider/Circle2D.h>
namespace doom
{
	class CircleCollider2D : public Collider2DComponent
	{
		friend class physics::Physics_Server;
	private:

		physics::Circle2D mCircle2D;

		float mRadius;

		void UpdateCorePhysicsVariable() override;
		virtual void SolveCollision() final;

	protected:
		void AutoColliderSetting() override;

	public:
	

		void SetRadius(float radius);
		float GetRadius();


	};
}
