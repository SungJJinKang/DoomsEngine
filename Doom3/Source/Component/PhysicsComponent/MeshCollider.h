#pragma once
#include "Collider3DComponent.h"

namespace doom
{
	class DOOM_API MeshCollider : public Collider3DComponent
	{
		DOBJECT_BODY(MeshCollider)

		friend class physics::Physics_Server;
	private:

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
	

	public:

		// Inherited via Collider3DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() override;

		virtual physics::Collider* GetWorldCollider() final;

	};

}