#pragma once

#include "../Core.h"
#include "../Graphics/Graphics_Server.h"

#include <Vector2.h>
#include <Physics/Collider/Ray.h>

namespace doom
{
	class GameCore;
	class ColliderComponent;
	namespace physics
	{
		class Collider;
		class Picking : public ISingleton<Picking>
		{
			friend class Physics_Server;
		private:

			//void UpdatePicking();

			//bool mIsTryPickingAtCurrentFrame{ false };
			//math::Vector2 mPickingNDCPoint{};
		public:


			static doom::physics::Ray GetCurrentCursorPointWorldRay();
			static ::doom::ColliderComponent* TryPicking();
			static bool CheckPicking(Collider* collider);
		};
	}
}

