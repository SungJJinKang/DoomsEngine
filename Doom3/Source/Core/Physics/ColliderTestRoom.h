#pragma once

#include <vector>
#include "Game/IGameFlow.h"
#include "Singleton.h"

namespace doom
{
	namespace physics
	{
		class Collider;
		class ColliderTestRoom : public ISingleton<ColliderTestRoom>
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

			void AddTestCollider(Collider* collider);
		};
	}
}

