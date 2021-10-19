#pragma once
#include "Collider2DComponent.h"
#include <Collider/Circle2D.h>
namespace doom
{
	class DOOM_API CircleCollider2D : public Collider2DComponent
	{
		DOBJECT_CLASS_BODY(CircleCollider2D)
		DOBJECT_CLASS_BASE_CHAIN(Collider2DComponent)

		friend class physics::Physics_Server;
	private:

		physics::Circle2D mLocalCircle2D;
		physics::Circle2D mWorldCircle2D;

		FLOAT32 mRadius;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
		

	public:
	

		void SetRadius(FLOAT32 radius);
		FLOAT32 GetRadius();


		// Inherited via Collider2DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
