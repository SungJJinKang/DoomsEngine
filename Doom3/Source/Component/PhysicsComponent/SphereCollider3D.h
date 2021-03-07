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
		physics::Sphere mLocalSpere;
		physics::Sphere mWorldSpere;

		float mRadius;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSetting() override;
		virtual physics::Collider* GetWorldCollider() final;

	public:
	

		void SetRadius(float radius);
		float GetRadius();


		


	};
}
