#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>

namespace doom
{
	class MeshCollider : public Collider3DComponent
	{
		friend class physics::Physics_Server;
	private:

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
		virtual physics::Collider* GetWorldCollider() final;

	public:

		// Inherited via Collider3DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() override;

	};

}