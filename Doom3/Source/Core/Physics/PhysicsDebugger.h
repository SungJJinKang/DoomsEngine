#pragma once

#include <Core.h>
#include <Graphics/Graphics_Core.h>

namespace doom
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
			inline extern void UpdateDebugger()
			{
			}
#endif
		

		};
	}
}

