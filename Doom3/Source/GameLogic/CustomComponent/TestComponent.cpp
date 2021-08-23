#include "TestComponent.h"
#include "Physics/Physics_Server.h"

#include <Physics/ColliderPickingTestRoom.h>
#include <Picking.h>

void doom::TestComponent::InitComponent()
{
	physics::Physics_Server::GetSingleton()->IsShowDebug = true;

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
	line.DrawPhysicsDebug();
	plane.DrawPhysicsDebug();
	aabb1.DrawPhysicsDebug();
	aabb2.DrawPhysicsDebug();
	aabb3.DrawPhysicsDebug();
	circle2d.DrawPhysicsDebug();
	sphere.DrawPhysicsDebug();
	sphere1.DrawPhysicsDebug();

	auto pickingRay = physics::Picking::GetCurrentCursorPointWorldRay();
	pickingRay.DrawPhysicsDebugColor(eColor::Green);

	if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F2))
	{
		D_DEBUG_LOG(std::to_string(time::MainTimer::GetCurrentFrame()), eLogType::D_ALWAYS);
	}
#endif

}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
