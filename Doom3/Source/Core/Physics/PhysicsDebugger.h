#pragma once

#include <Core.h>
#include <Graphics/Graphics_Core.h>

namespace doom
{
	namespace physics
	{
		class DOOM_API PhysicsDebugger
		{

		private:

			void DrawMouseRayCast();
			void DrawPhysicsColliderBoundingBox();

		public:

#ifdef DEBUG_DRAWER
			void UpdateDebugger()
			{
				DrawMouseRayCast();
				DrawPhysicsColliderBoundingBox();
			}
#else
			void UpdateDebugger()
			{
			}
#endif
		

		};
	}
}

