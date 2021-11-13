#pragma once
#include "Collider3DComponent.h"

#include "MeshCollider.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS MeshCollider : public Collider3DComponent
	{
		GENERATE_BODY()
		

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