#include "PhysicsDebugger.h"

#include "Physics_Server.h"
#include "Collider/Ray.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Physics/Collider/ColliderSolution.h>

void doom::physics::PhysicsDebugger::DrawMouseRayCast()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();
	mouseRay.DrawPhysicsDebugColor(eColor::Green);
}

void doom::physics::PhysicsDebugger::DrawPhysicsColliderBoundingBox()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();


	const std::vector<ColliderComponent*> colliderComponents = StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (ColliderComponent* col : colliderComponents)
	{
		bool isOverlap = ColliderSolution::CheckIsOverlap(&mouseRay, col->GetWorldCollider());
		const eColor debugColor = (isOverlap == true ? eColor::Red : eColor::Blue);
		col->GetWorldCollider()->DrawPhysicsDebugColor(debugColor);
	}
}
