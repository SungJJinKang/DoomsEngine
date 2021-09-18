#include "Collider.h"


#include "ColliderSolution.h"
#include "../../Graphics/DebugGraphics.h"

void doom::physics::Collider::ClearCollision()
{
	bmIsCollideAtCurrentFrame = false;
}
