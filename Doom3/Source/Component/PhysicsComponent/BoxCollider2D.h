#pragma once
#include "Collider2DComponent.h"
#include <Vector2.h>
#include <Collider/AABB.h>
namespace doom
{
	class DOOM_API BoxCollider2D : public Collider2DComponent
	{
		friend class physics::Physics_Server;
	private:

		/// <summary>
		/// world aabb
		/// </summary>
		physics::AABB2D mLocalAABB2D;
		physics::AABB2D mWorldAABB2D;

		/// <summary>
		/// positive extent,
		/// </summary>
		math::Vector2 mHalfExtent;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSettingFromAABB3D(const physics::AABB3D& aabb3dFromMesh) final;


	public:
		void SetFromAABB2D(const physics::AABB2D& aabb2D);

		void SetHalfExtent(const math::Vector2& halfExtent);
		math::Vector2 GetHalfExtent() const;
		
		// Inherited via Collider2DComponent
		virtual doom::physics::AABB3D ExtractLocalAABB3D() final;

		virtual physics::Collider* GetWorldCollider() final;
	};
}
