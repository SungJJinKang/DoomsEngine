#pragma once

#include "../Core.h"
#include "../Graphics/Graphics_Server.h"

#include <Vector2.h>
#include "../Singleton.h"

namespace doom
{
	class GameCore;
	class ColliderComponent;
	namespace physics
	{
		class Picking : public ISingleton<Picking>
		{
			friend class Physics_Server;
		private:

			void UpdatePicking();

		public:

			// TODO : BVH
			static ::doom::ColliderComponent* TryPicking(const math::Vector2 mousePoint);
		};
	}
}

