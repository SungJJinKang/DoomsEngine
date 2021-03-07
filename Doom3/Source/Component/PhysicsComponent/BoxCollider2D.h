#pragma once
#include "Collider2DComponent.h"
#include <Vector2.h>
#include <Collider/AABB.h>
namespace doom
{
	class BoxCollider2D : public Collider2DComponent
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

		void AutoColliderSetting() override;

		virtual physics::Collider* GetWorldCollider() final;

	public:
		void SetAABB2D(const physics::AABB2D& aabb2D);

		void SetHalfExtent(const math::Vector2& halfExtent);
		math::Vector2 GetHalfExtent() const;

	};
}
