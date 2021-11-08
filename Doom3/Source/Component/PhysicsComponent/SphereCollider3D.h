#pragma once
#include "Collider3DComponent.h"
#include <Collider/Sphere.h>
namespace dooms
{
	class DOOM_API D_CLASS SphereCollider3D : public Collider3DComponent
	{
		DOBJECT_CLASS_BODY(SphereCollider3D)
		DOBJECT_CLASS_BASE_CHAIN(Collider3DComponent)

		friend class physics::Physics_Server;
	private:
		physics::Sphere mLocalSpere;
		physics::Sphere mWorldSpere;

		FLOAT32 mRadius;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
	
	public:
	
		void SetRadius(FLOAT32 radius);
		FLOAT32 GetRadius();

		// Inherited via Collider3DComponent
		virtual dooms::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
