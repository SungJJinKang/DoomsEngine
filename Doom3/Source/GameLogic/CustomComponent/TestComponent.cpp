#include "TestComponent.h"
#include "Physics/Physics_Server.h"

#include <Physics/ColliderPickingTestRoom.h>
#include <Picking.h>

void doom::TestComponent::InitComponent()
{
	physics::Physics_Server::GetSingleton()->IsShowDebug = true;

#ifdef DEBUG_MODE
	//Ignore dirty codes
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->line));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->plane));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->aabb1));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->aabb2));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->aabb3));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->sphere));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->sphere1));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->circle2d));
#endif

}

void doom::TestComponent::UpdateComponent()
{

	//Ignore dirty codes
#ifdef DEBUG_MODE
	this->line.DrawPhysicsDebug();
	this->plane.DrawPhysicsDebug();
	this->aabb1.DrawPhysicsDebug();
	this->aabb2.DrawPhysicsDebug();
	this->aabb3.DrawPhysicsDebug();
	this->circle2d.DrawPhysicsDebug();
	this->sphere.DrawPhysicsDebug();
	this->sphere1.DrawPhysicsDebug();

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
