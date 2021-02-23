#pragma once
#include "Collider3D.h"
#include <Vector3.h>
#include <CapsuleCollider.h>
namespace doom
{
	class CapsuleCollider3D : public Collider3D
	{
	private:

		physics::CapsuleCollider mCapsuleCollider;

		float mHeight;
		float mRadius;

		void UpdateCorePhysicsVariable() override;
		virtual void _UpdatePhysics() final;

	public:
		

		void SetHeight(float height);
		float GetHeight();
		void SetRadius(float radius);
		float GetRadius();
	};
}
