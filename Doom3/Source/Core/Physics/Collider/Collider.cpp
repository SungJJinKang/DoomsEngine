#include "Collider.h"


#include "ColliderSolution.h"
#include "../../Graphics/DebugGraphics.h"

void doom::physics::Collider::ClearCollision()
{
	this->bmIsCollision = false;
}

void doom::physics::Collider::DrawPhysicsDebug()
{
	if (this->bmIsCollision)
	{
		RenderPhysics::DrawPhysicsDebugColor(eColor::Red);
	}
	else
	{
		RenderPhysics::DrawPhysicsDebugColor(graphics::DebugGraphics::mDefaultDebugColor);
	}
	
}
