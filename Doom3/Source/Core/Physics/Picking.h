#pragma once

#include "../Core.h"
#include "../Graphics/Graphics_Server.h"

#include <PhysicsComponent/Collider.h>
#include <Vector2.h>
namespace doom
{
	class GameCore;

	namespace userinput
	{
		class Picking
		{
		private:

		protected:

		public:

			// TODO : BVH
			static Collider TryPicking(const math::Vector2 mousePoint);
		};
	}
}

