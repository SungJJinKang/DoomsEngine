#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>
#include <Collider/AABB.h>
namespace doom
{
	class BoxCollider3D : public Collider3DComponent
	{
		friend class physics::Physics_Server;
	private:

		physics::AABB3D mAABB3D;

		math::Vector3 mHalfExtent;

		void UpdateCorePhysicsVariable() override;
		virtual void SolveCollision() final;
		void UpdateHalfExtent();
		void AutoColliderSetting() override;

	public:		
		void SetAABB3D(const physics::AABB3D& aabb3D);
		math::Vector3 GetHalfExtent();

	};
}
