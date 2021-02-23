#pragma once
#include "Collider2D.h"
#include <Vector2.h>
#include <AABB.h>
namespace doom
{
	class BoxCollider2D : public Collider2D
	{
	private:

		physics::AABB2D mAABB2D;

		/// <summary>
		/// positive extent,
		/// </summary>
		math::Vector2 mHalfExtent;

		void UpdateCorePhysicsVariable() override;
		virtual void _UpdatePhysics() final;

	public:
	
			
		void SetHalfExtent(const math::Vector2& halfExtent);
		math::Vector2 GetHalfExtent();

	};
}
