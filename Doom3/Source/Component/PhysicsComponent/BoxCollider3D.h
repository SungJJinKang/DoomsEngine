#pragma once
#include "Collider3D.h"
#include <Vector3.h>
#include <AABB.h>
namespace doom
{
	class BoxCollider3D : public Collider3D
	{
	private:

		physics::AABB3D mAABB3D;

		math::Vector3 mHalfExtent;

		void UpdateCorePhysicsVariable() override;
		virtual void _UpdatePhysics() final;

	public:
		

		void SetHalfExtent(const math::Vector3& halfExtent);
		math::Vector3 GetHalfExtent();

	};
}
