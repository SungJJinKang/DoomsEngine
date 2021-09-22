#include "Collider.h"


#include "ColliderSolution.h"
#include "../../Graphics/DebugGraphics/DebugDrawer.h"

void doom::physics::Collider::ClearCollision()
{
	bmIsCollideAtCurrentFrame = false;
}
