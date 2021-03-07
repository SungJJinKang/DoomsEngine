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

		void AutoColliderSetting() override;
		virtual physics::Collider* GetWorldCollider() final;
	public:

	
	};

}