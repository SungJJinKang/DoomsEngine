#pragma once
#include "../Core/ServerComponent.h"
#include <StaticContainer/StaticContainer.h>
#include <Physics/Collider/AABB.h>

namespace doom
{
	namespace physics 
	{
		class Physics_Server;
	}

	class ColliderComponent : public ServerComponent, public StaticContainer<ColliderComponent>
	{
		friend class physics::Physics_Server;
	private:

		void ResetAllCollisionState();
	
	protected:

		DirtyReceiver mTransformDirtyReceiver;
		LocalDirty bmIsCorePhysicsVariableDirty{ true };

		bool bmIsTrigger{ false };

		bool mbIsColliderEnter{ false };
		bool mbIsColliderExit{ false };
		bool mbIsColliderStay{ false };
		
		bool mbIsTriggerEnter{ false };
		bool mbIsTriggerExit{ false };
		bool mbIsTriggerStay{ false };
		


		void InitComponent() override;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() override;
		void OnDestroy() override;
		void OnActivated() override;
		void OnDeActivated() override;

		virtual void UpdateCorePhysicsVariable() = 0;
		virtual void SolveCollision() = 0;

		/// <summary>
		/// Set Collider variable depending on Renderer's mesh
		/// </summary>
		virtual void AutoColliderSetting() = 0;
		/// <summary>
		/// return true if There is Renderer and have AABB3D
		/// </summary>
		/// <param name="aabb3D">aabb will be set by reference</param>
		/// <returns></returns>
		bool GetMeshAABB3D(physics::AABB3D& aabb3D);

	public:

		void OnPreUpdatePhysics();
		void UpdatePhysics();
		void OnPostUpdatePhysics();

		bool GetIsColliderEnter()
		{
			return this->mbIsColliderEnter;
		}

		bool GetIsColliderExit()
		{
			return this->mbIsColliderExit;
		}

		bool GetIsColliderStay()
		{
			return this->mbIsColliderStay;
		}


		bool GetIsTriggerEnter()
		{
			return this->mbIsTriggerEnter;
		}

		bool GetIsTriggerExit()
		{
			return this->mbIsTriggerExit;
		}

		bool GetIsTriggerStay()
		{
			return this->mbIsTriggerStay;
		}

	};
}
