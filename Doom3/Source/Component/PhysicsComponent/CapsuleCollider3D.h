#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>
#include <Collider/CapsuleCollider.h>
namespace doom
{
	class CapsuleCollider3D : public Collider3DComponent
	{
		friend class physics::Physics_Server;
	private:

		physics::CapsuleCollider mCapsuleCollider;

		float mHeight;
		float mRadius;

		void UpdateCorePhysicsVariable() override;
		virtual void SolveCollision() final;

	protected:
		void AutoColliderSetting() override;

	public:
		

		void SetHeight(float height);
		float GetHeight();
		void SetRadius(float radius);
		float GetRadius();


	};
}
