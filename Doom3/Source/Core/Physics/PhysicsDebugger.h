#pragma once

#include <Core.h>

namespace doom
{
	namespace physics
	{
		class PhysicsDebugger
		{

		private:

			void DrawMouseRayCast();
			void DrawPhysicsColliderBoundingBox();

		public:

#ifdef DEBUG_MODE
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

