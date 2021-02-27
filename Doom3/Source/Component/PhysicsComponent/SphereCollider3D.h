#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>
#include <Collider/Sphere.h>
namespace doom
{
	class SphereCollider3D : public Collider3DComponent
	{
		friend class physics::Physics_Server;
	private:
		physics::Sphere mSpere;

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
