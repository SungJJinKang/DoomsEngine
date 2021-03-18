#include "TestComponent.h"
#include "Physics/Physics_Server.h"

#include <Physics/ColliderPickingTestRoom.h>
#include <Picking.h>

void doom::TestComponent::InitComponent()
{
	physics::Physics_Server::GetSingleton()->IsShowDebug = true;

	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->line));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->plane));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->aabb));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->sphere));
	physics::ColliderPickingTestRoom::GetSingleton()->AddTestCollider(&(this->circle2d));
		
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

	if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F2))
	{
		D_DEBUG_LOG(std::to_string(time::MainTimer::GetCurrentFrame()), eLogType::D_ALWAYS);
	}
}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
