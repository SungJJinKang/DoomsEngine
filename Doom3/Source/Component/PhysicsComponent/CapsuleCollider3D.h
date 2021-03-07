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

		physics::CapsuleCollider mLocalCapsuleCollider;
		physics::CapsuleCollider mWorldCapsuleCollider;

		float mHeight;
		float mRadius;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSetting() override;
		virtual physics::Collider* GetWorldCollider() final;

	public:
		

		void SetHeight(float height);
		float GetHeight();
		void SetRadius(float radius);
		float GetRadius();

		

	};
}
