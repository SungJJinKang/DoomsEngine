#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>
#include <Collider/AABB.h>
namespace doom
{
	class DOOM_API BoxCollider3D : public Collider3DComponent
	{
		DOBJECT_CLASS_BODY(BoxCollider3D)
		DOBJECT_CLASS_BASE_CHAIN(Collider3DComponent)

		friend class physics::Physics_Server;
	private:

		/// <summary>
		/// world aabb
		/// </summary>
		physics::AABB3D mLocalAABB3D;
		physics::AABB3D mWorldAABB3D;

		math::Vector3 mHalfExtent;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;
	



	public:		
		void SetFromAABB3D(const physics::AABB3D& aabb3D);

		void SetHalfExtent(const math::Vector3& halfExtent);
		math::Vector3 GetHalfExtent() const;

		// Inherited via Collider3DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() final;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
