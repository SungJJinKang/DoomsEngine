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

		/// <summary>
		/// world aabb
		/// </summary>
		physics::AABB3D mLocalAABB3D;
		physics::AABB3D mWorldAABB3D;

		math::Vector3 mHalfExtent;

		virtual void UpdateLocalCollider() final;
		virtual void UpdateWorldCollider() final;

		void AutoColliderSetting() override;
		virtual physics::Collider* GetWorldCollider() final;

	public:		
		void SetAABB3D(const physics::AABB3D& aabb3D);

		void SetHalfExtent(const math::Vector3& halfExtent);
		math::Vector3 GetHalfExtent() const;

	
	};
}
