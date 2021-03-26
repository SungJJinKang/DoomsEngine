#pragma once
#include "../Core.h"
#include "../Game/IGameFlow.h"
#include "Picking.h"
#include "ColliderPickingTestRoom.h"

#include "utility/BVH/BVH.h"

#define PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT 30000 // this include all internal node, leaf node

namespace doom
{
	class ColliderComponent;
	namespace physics
	{
		class Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{

			friend class GameCore;
			friend class AABB3D;
			friend class AABB2D;
			friend class ::doom::ColliderComponent;
		private:

			bool bmIsPhysicsOn{ true };

			BVHAABB3D mPhysicsColliderBVH{ PHYSICS_COLLIDER_BVH_MAX_NODE_COUNT };

			float FIXED_TIME_STEP{};
			int MAX_PHYSICS_STEP{ 8 };

			float ENLARGED_AABB2D_OFFSET{};
			float ENLARGED_AABB3D_OFFSET{};
			

			Picking mPicking{};
#ifdef DEBUG_MODE
			ColliderPickingTestRoom mColliderTestRoom{};
#endif
			virtual void Init() final;
			virtual void Update() final;
			virtual void FixedUpdate() final
			{
				D_START_PROFILING("FixedUpdateCollision", eProfileLayers::CPU);
				this->FixedUpdateCollision();
				D_END_PROFILING("FixedUpdateCollision");

				//D_START_PROFILING("UpdatePicking", eProfileLayers::CPU);
				//this->mPicking.UpdatePicking();
				//D_END_PROFILING("UpdatePicking");
			}

			void FixedUpdateCollision();

			void DrawDebugColliderComponents();
			void SolveColliderComponents();

			virtual void OnEndOfFrame() final;

			void QueryCollision();

		public:
			static inline bool IsShowDebug{ true };

		};

	}
}

