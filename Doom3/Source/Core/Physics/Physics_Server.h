#pragma once
#include "../Core.h"

#include "../Game/IGameFlow.h"

#include <Simple_SingleTon/Singleton.h>
#include <Misc/AccelerationContainer/BVH/BVH.h>

#define PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT 3000 // this include all internal node, leaf node

#include "Physics_Server.reflection.h"
namespace dooms
{
	class ColliderComponent;
	D_NAMESPACE(dooms::physics)
	namespace physics
	{
		class DOOM_API D_CLASS Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{
			GENERATE_BODY()
			

		private:

			void LoadPhysicsSetting();
			void ResetCollisionData();

		public:
			
			BVHAABB3D mPhysicsColliderBVH;

			Physics_Server();
			~Physics_Server();

			virtual void Init(const int argc, char* const* const argv) final;
			virtual void Update() final;
			virtual void FixedUpdate() final;
			void FixedUpdateCollision();
			


			void SolveColliderComponents();

			virtual void OnEndOfFrame() final;

			void QueryCollision();


		};

	}
}

