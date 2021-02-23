#include "TestComponent.h"
#include "Physics/Physics_Server.h"


void doom::TestComponent::InitComponent()
{
	physics::Physics_Server::GetSingleton()->IsShowDebug = true;
}

void doom::TestComponent::UpdateComponent()
{
	this->line.DebugRender();
	this->plane.DebugRender();
	this->aabb.DebugRender();
}

void doom::TestComponent::OnEndOfFrame_Component()
{

}
