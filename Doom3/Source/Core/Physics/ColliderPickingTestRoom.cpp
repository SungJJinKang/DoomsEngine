#include "Core.h"
#include "ColliderPickingTestRoom.h"

#ifdef DEBUG_MODE



#include "Picking.h"

#include <Physics/Physics_Server.h>

#include "Collider/Collider.h"
#include "Collider/ColliderSolution.h"


void doom::physics::ColliderPickingTestRoom::FixedUpdatePhysics()
{

	doom::physics::Ray cursorRay{ Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay() };
	for (unsigned int i = 0; i < mTestColliders.size(); i++)
	{
		mTestColliders[i]->ClearCollision();
		bool isOverlap = ColliderSolution::CheckIsOverlap(&cursorRay, mTestColliders[i]);
		if (isOverlap)
		{
			mTestColliders[i]->bmIsCollideAtCurrentFrame = true;
		}
	}

}

void doom::physics::ColliderPickingTestRoom::DrawDebug()
{
	for (unsigned int i = 0; i < mTestColliders.size(); i++)
	{
		mTestColliders[i]->DrawPhysicsDebugColor(eColor::Green);
		
	}
}

void doom::physics::ColliderPickingTestRoom::AddTestCollider(Collider* collider)
{
	mTestColliders.push_back(collider);
}

#endif