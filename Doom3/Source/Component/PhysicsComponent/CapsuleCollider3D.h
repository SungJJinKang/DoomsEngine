#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>
#include <Collider/CapsuleCollider.h>
namespace doom
{
	class DOOM_API CapsuleCollider3D : public Collider3DComponent
	{
		friend class physics::Physics_Server;
	private:

		physics::CapsuleCollider mLocalCapsuleCollider;
		physics::CapsuleCollider mWorldCapsuleCollider;

		float mHeight;
		float mRadius;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
		


	public:
	
		void SetHeight(float height);
		float GetHeight();
		void SetRadius(float radius);
		float GetRadius();
		
		// Inherited via Collider3DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
