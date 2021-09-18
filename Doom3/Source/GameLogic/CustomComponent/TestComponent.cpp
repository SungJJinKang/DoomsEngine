#include "TestComponent.h"
#include "Physics/Physics_Server.h"

#include <Physics/ColliderPickingTestRoom.h>
#include <Picking.h>

void doom::TestComponent::InitComponent()
{
	physics::Physics_Setting::bmIsRenderPhysicsCollider = true;

#ifdef DEBUG_MODE
	//Ignore dirty codes
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(line));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(plane));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(aabb1));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(aabb2));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(aabb3));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(sphere));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(sphere1));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(circle2d));
#endif

}

void doom::TestComponent::UpdateComponent()
{

	//Ignore dirty codes
#ifdef DEBUG_MODE
	line.DrawPhysicsDebugColor(eColor::Green);
	plane.DrawPhysicsDebugColor(eColor::Green);
	aabb1.DrawPhysicsDebugColor(eColor::Green);
	aabb2.DrawPhysicsDebugColor(eColor::Green);
	aabb3.DrawPhysicsDebugColor(eColor::Green);
	circle2d.DrawPhysicsDebugColor(eColor::Green);
	sphere.DrawPhysicsDebugColor(eColor::Green);
	sphere1.DrawPhysicsDebugColor(eColor::Green);

	auto pickingRay = doom::physics::Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();
	pickingRay.DrawPhysicsDebugColor(eColor::Green);


#endif

}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
