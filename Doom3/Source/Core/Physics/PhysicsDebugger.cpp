#include "PhysicsDebugger.h"

#include "Physics_Server.h"
#include "Collider/Ray.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Rendering/Camera.h>
#include <Scene/Entity.h>
#include "PhysicsSolver.h"

void doom::physics::PhysicsDebugger::DrawMouseRayCast()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();
	mouseRay.DrawPhysicsDebugColor(eColor::Green);
}

void doom::physics::PhysicsDebugger::DrawPhysicsColliderBoundingBox()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();

	
	const std::vector<ColliderComponent*> colliderComponents = StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (ColliderComponent* colComponent : colliderComponents)
	{
		doom::physics::Collider* const col = colComponent->GetWorldCollider();
		if(col->bmIsCollideAtCurrentFrame == true)
		{
			col->DrawPhysicsDebugColor(eColor::Red);
		}
		else
		{
			col->DrawPhysicsDebugColor(eColor::Blue);
		}
		
	}
	

}
