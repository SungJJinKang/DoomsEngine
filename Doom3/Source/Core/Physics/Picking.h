#pragma once

#include "../Core.h"

#include <Physics/Collider/Ray.h>

namespace doom
{
	namespace physics
	{
		namespace Picking 
		{
			extern doom::physics::Ray GetCurrentCursorPointWorldRay();
		};
	}
}

