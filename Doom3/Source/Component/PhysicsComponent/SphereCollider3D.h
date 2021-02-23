#pragma once
#include "Collider3D.h"
#include <Vector3.h>
#include <Sphere.h>
namespace doom
{
	class SphereCollider3D : public Collider3D
	{
	private:
		physics::Sphere mSpere;

		float mRadius;

		void UpdateCorePhysicsVariable() override;
		virtual void _UpdatePhysics() final;

	public:
	

		void SetRadius(float radius);
		float GetRadius();

	};
}
