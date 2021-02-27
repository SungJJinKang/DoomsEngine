#pragma once
#include "Collider3DComponent.h"
#include <Vector3.h>

namespace doom
{
	class MeshCollider : public Collider3DComponent
	{
		friend class physics::Physics_Server;
	private:

		void UpdateCorePhysicsVariable() override;
		virtual void SolveCollision() final;

	protected:

		void AutoColliderSetting() override;

	public:

	};

}