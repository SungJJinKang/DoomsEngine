#pragma once
#include "../Core.h"

#include "../Game/IGameFlow.h"
#include "Phycis_Core.h"

#include "Picking.h"
#include "PhysicsDebugger.h"

#include "utility/BVH/BVH.h"

#define PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT 30000 // this include all internal node, leaf node

namespace doom
{
	class ColliderComponent;
	namespace physics
	{
		class Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{
		private:

			void UpdatePhysicsOnOff();
			void LoadPhysicsSetting();
			
		public:

			PhysicsDebugger mPhysicsDebugger;

			Picking mPicking{};
			BVHAABB3D mPhysicsColliderBVH{ PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT };

			virtual void Init() final;
			virtual void Update() final;
			virtual void FixedUpdate() final
			{
				D_START_PROFILING("FixedUpdateCollision", eProfileLayers::CPU);
				FixedUpdateCollision();
				D_END_PROFILING("FixedUpdateCollision");

				D_START_PROFILING("UpdatePicking", eProfileLayers::CPU);
				//mPicking.UpdatePicking();
				D_END_PROFILING("UpdatePicking");
			}
			void FixedUpdateCollision();

			void SolveColliderComponents();

			virtual void OnEndOfFrame() final;

			void QueryCollision();


		};

	}
}

