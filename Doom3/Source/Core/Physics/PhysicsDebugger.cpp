#include "PhysicsDebugger.h"

#include "Physics_Server.h"
#include "Collider/Ray.h"


void doom::physics::PhysicsDebugger::DrawMouseRayCast()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();
	mouseRay.DrawPhysicsDebugColor(eColor::Green);
}
