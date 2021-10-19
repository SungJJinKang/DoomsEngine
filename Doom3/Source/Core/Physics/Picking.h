#pragma once

#include "../Core.h"

#include <Physics/Collider/Ray.h>

namespace doom
{
	class GameCore;
	class ColliderComponent;
	namespace physics
	{
		class Collider;
		//TODO : Change to namespace 
		namespace Picking 
		{
			extern doom::physics::Ray GetCurrentCursorPointWorldRay();
		};
	}
}

