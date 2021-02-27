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

		physics::AABB2D mAABB2D;

		/// <summary>
		/// positive extent,
		/// </summary>
		math::Vector2 mHalfExtent;

		void UpdateCorePhysicsVariable() override;
		virtual void SolveCollision() final;
		void UpdateHalfExtent();
		void AutoColliderSetting() override;

	public:
		void SetAABB2D(const physics::AABB2D& aabb2D);
		math::Vector2 GetHalfExtent();

	};
}
