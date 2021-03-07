#include "Collider.h"


#include "ColliderSolution.h"
#include "../../Graphics/DebugGraphics.h"

void doom::physics::Collider::ClearCollision()
{
	this->bmIsCollision = false;
}

void doom::physics::Collider::CheckCollision(Collider* collider)
{
	D_ASSERT(collider != nullptr);

	auto solution = ColliderSolution::GetCollisionAlgorithm(this, collider);
	if (solution != nullptr)
	{
		bool IsCollision = solution(this, collider);
		if (IsCollision == true)
		{
			this->bmIsCollision = true;
			collider->bmIsCollision = true;
		}
		else
		{
			//Never Do This, Reset will be called in Physcis_Server
			//this->bmIsCollision = false;
			//collider->bmIsCollision = false;
		}

	}
	
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
