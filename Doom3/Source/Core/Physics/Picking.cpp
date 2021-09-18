#include "Picking.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Rendering/Camera.h>
#include <UserInput_Server.h>
#include <Transform.h>

doom::physics::Ray doom::physics::Picking::GetCurrentCursorPointWorldRay()
{
	math::Vector3 currentNDCCursorPoint{ userinput::UserInput_Server::GetCurrentMouseNDCPosition() };
	currentNDCCursorPoint.z = 1;

	math::Vector3 normalWorldPoint = Camera::GetMainCamera()->NDCToWorldPoint(currentNDCCursorPoint); // In NDC coordinate, forward had positive z value, so put minus

	return physics::Ray(userinput::UserInput_Server::GetCurrentMouseWorldPosition(), normalWorldPoint);

}

::doom::ColliderComponent* doom::physics::Picking::TryPicking()
{
	auto ray = Picking::GetCurrentCursorPointWorldRay();

	//Loop Possible All Colliders

	return nullptr;
}

bool doom::physics::Picking::CheckPicking(Collider* collider)
{
	auto ray = Picking::GetCurrentCursorPointWorldRay();

	return true;
}
