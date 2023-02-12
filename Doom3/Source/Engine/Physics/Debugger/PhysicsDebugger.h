#pragma once

#include <Core.h>
#include <Graphics/Graphics_Core.h>

namespace dooms
{
	namespace physics
	{
		namespace PhysicsDebugger
		{
			extern void DrawMouseRayCast();
			extern void DrawPhysicsColliderBoundingBox();
			
#ifdef DEBUG_DRAWER
			extern void UpdateDebugger();
#else
			inline void UpdateDebugger()
			{
			}
#endif
		

		};
	}
}

