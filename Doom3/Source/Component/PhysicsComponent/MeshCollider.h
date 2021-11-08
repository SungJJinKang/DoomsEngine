#pragma once
#include "Collider3DComponent.h"

namespace dooms
{
	class DOOM_API D_CLASS MeshCollider : public Collider3DComponent
	{
		DOBJECT_CLASS_BODY(MeshCollider)
		DOBJECT_CLASS_BASE_CHAIN(Collider3DComponent)

		friend class physics::Physics_Server;
	private:

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
	

	public:

		// Inherited via Collider3DComponent
		virtual dooms::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;

	};

}