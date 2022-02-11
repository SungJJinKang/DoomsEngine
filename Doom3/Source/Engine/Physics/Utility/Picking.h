#pragma once

#include "../Core.h"

#include <Physics/Collider/Ray.h>

namespace dooms
{
	namespace physics
	{
		namespace Picking 
		{
			extern dooms::physics::Ray GetCurrentCursorPointWorldRay();
		};
	}
}

