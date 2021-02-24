#include "TestComponent.h"
#include "Physics/Physics_Server.h"


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
}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
