#include "TestComponent.h"
#include "Physics/Physics_Server.h"

#include <Picking.h>

void doom::TestComponent::InitComponent()
{
	physics::Physics_Server::GetSingleton()->IsShowDebug = true;
}

void doom::TestComponent::UpdateComponent()
{
	this->line.DrawPhysicsDebug();
	this->plane.DrawPhysicsDebug();
	this->aabb.DrawPhysicsDebug();
	//this->circle2d.DrawPhysicsDebug();
	this->sphere.DrawPhysicsDebug();

	auto pickingRay = physics::Picking::GetCurrentCursorPointWorldRay();
	pickingRay.DrawPhysicsDebug(eColor::Green);
	D_DEBUG_LOG({ "origin : ", pickingRay.mOrigin.toString(), " normal : ", pickingRay.GetNormal().toString() });
}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
