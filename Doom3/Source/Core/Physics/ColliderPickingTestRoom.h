#pragma once

#ifdef DEBUG_MODE

#include <vector>
#include "../Core.h"
#include "Game/IGameFlow.h"

namespace doom
{
	namespace physics
	{
		class Collider;
		class ColliderPickingTestRoom : public ISingleton<ColliderPickingTestRoom>
		{
			friend class Physics_Server;
		private:
			/// <summary>
			/// Every Collider will be debug rendered
			/// if Collider collide with other collider, it will color red
			/// </summary>
			std::vector<Collider*> mTestColliders{};

		public:
			void FixedUpdatePhysics();
			void DrawDebug();
			void AddTestCollider(Collider* collider);
		};
	}
}

#endif