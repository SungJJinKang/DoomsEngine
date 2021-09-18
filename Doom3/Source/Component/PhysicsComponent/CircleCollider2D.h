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

		physics::Circle2D mLocalCircle2D;
		physics::Circle2D mWorldCircle2D;

		float mRadius;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
		

	public:
	

		void SetRadius(float radius);
		float GetRadius();


		// Inherited via Collider2DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
