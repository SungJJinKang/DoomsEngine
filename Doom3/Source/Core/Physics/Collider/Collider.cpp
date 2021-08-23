#include "Collider.h"


#include "ColliderSolution.h"
#include "../../Graphics/DebugGraphics.h"

void doom::physics::Collider::ClearCollision()
{
	bmIsCollision = false;
}

#ifdef DEBUG_MODE
void doom::physics::Collider::DrawPhysicsDebug(bool drawInstantly)
{
	if (bmIsCollision)
	{
		RenderPhysics::DrawPhysicsDebugColor(eColor::Red, drawInstantly);
	}
	else
	{
		RenderPhysics::DrawPhysicsDebugColor(graphics::DebugGraphics::mDefaultDebugColor, drawInstantly);
	}
	
}
#endif
