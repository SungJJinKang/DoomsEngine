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

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
		virtual physics::Collider* GetWorldCollider() final;

	public:
	
		void SetRadius(float radius);
		float GetRadius();

		// Inherited via Collider3DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() override;

	};
}
