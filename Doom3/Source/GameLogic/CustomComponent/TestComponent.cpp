#include "TestComponent.h"
#include "Physics/Physics_Server.h"

#include <Physics/ColliderPickingTestRoom.h>
#include <Picking.h>

void doom::TestComponent::InitComponent()
{
	physics::Physics_Server::GetSingleton()->IsShowDebug = true;

	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->line));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->line));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->plane));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->aabb));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->sphere));
		
}

void doom::TestComponent::UpdateComponent()
{
	//this->line.DrawPhysicsDebug();
	//this->plane.DrawPhysicsDebug();
	//this->aabb.DrawPhysicsDebug();
	//this->circle2d.DrawPhysicsDebug();
	//this->sphere.DrawPhysicsDebug();

	auto pickingRay = physics::Picking::GetCurrentCursorPointWorldRay();
	pickingRay.DrawPhysicsDebugColor(eColor::Green);
}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
