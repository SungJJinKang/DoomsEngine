#include "ColliderPickingTestRoom.h"

#include "Picking.h"

#include "Collider/Collider.h"
#include "Collider/ColliderSolution.h"


void doom::physics::ColliderPickingTestRoom::FixedUpdatePhysics()
{
	auto cursorRay{ physics::Picking::GetCurrentCursorPointWorldRay() };
	for (unsigned int i = 0; i < this->mTestColliders.size(); i++)
	{
		bool isOverlap = ColliderSolution::CheckIsOverlap(&cursorRay, this->mTestColliders[i]);
		if (isOverlap)
		{
			this->mTestColliders[i]->bmIsCollision = true;
		}
	}
}

void doom::physics::ColliderPickingTestRoom::DrawDebug()
{
	for (unsigned int i = 0; i < this->mTestColliders.size(); i++)
	{
		this->mTestColliders[i]->DrawPhysicsDebug();
		this->mTestColliders[i]->ClearCollision();
	}
}

void doom::physics::ColliderPickingTestRoom::AddTestCollider(Collider* collider)
{
	this->mTestColliders.push_back(collider);
}
