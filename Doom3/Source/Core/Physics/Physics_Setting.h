#pragma once

#include <Core.h>

namespace doom
{
	namespace physics
	{
		class DOOM_API Physics_Setting
		{

		private:

			inline static bool bmIsPhysicsOn{ true };
	
		public:

			FORCE_INLINE static bool GetIsPhysicsOn()
			{
				return bmIsPhysicsOn;
			}
			static void SetIsPhysicsOn(const bool isOn);

			inline static bool IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER{ false };

			inline static bool IS_RENDER_PHYSICS_COLLIDER{ true };

			inline static FLOAT32 ENLARGED_AABB2D_OFFSET{};
			inline static FLOAT32 ENLARGED_AABB3D_OFFSET{};

		};
	}
}
