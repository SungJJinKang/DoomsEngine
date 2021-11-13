#pragma once
#include "Collider2DComponent.h"
#include <Collider/Circle2D.h>

#include "CircleCollider2D.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS CircleCollider2D : public Collider2DComponent
	{
		GENERATE_BODY()
		

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
		virtual dooms::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
