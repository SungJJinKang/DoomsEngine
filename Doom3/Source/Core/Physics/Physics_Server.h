#pragma once
#include "../Core.h"
#include "../Game/IGameFlow.h"
#include "Picking.h"
#include "ColliderPickingTestRoom.h"
#include "BVH/test/BVH_TestRoom.h"

namespace doom
{
	namespace physics
	{
		class Physics_Server : public IGameFlow, public ISingleton<Physics_Server>
		{

			friend class GameCore;

		private:
			Picking mPicking{};
#ifdef DEBUG_MODE
			ColliderPickingTestRoom mColliderTestRoom{};
			BVH_TestRoom mBVH_TestRoom{};
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

			float FIXED_TIME_STEP{};
			int MAX_PHYSICS_STEP{ 8 };
		};

	}
}

