#pragma once

#include <Core.h>

namespace doom
{
	namespace physics
	{
		class Physics_Setting
		{

		private:

			inline static bool bmIsPhysicsOn{ true };
	
		public:

			FORCE_INLINE static bool GetIsPhysicsOn()
			{
				return bmIsPhysicsOn;
			}
			static void SetIsPhysicsOn(const bool isOn);

			inline static bool bmIsRenderPhysicsCollider{ true };

			inline static float ENLARGED_AABB2D_OFFSET{};
			inline static float ENLARGED_AABB3D_OFFSET{};

		};
	}
}
