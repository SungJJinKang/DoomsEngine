#pragma once
#include "../Core/ServerComponent.h"
#include "../Iterator/ComponentStaticIterater.h"
namespace doom
{
	namespace physics 
	{
		class Physics_Server;
	}

	class Collider : public ServerComponent, public ComponentStaticIterater<Collider>
	{
		friend class physics::Physics_Server;
	private:

		void ResetAllState();
		virtual void UpdateCorePhysicsVariable() = 0;
	protected:

		bool bmIsCorePhysicsVariableDirty{ true };

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

		virtual void _UpdatePhysics() = 0;


	public:

		void UpdatePhysics();
	

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
