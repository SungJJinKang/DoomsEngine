#include "Picking.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Camera.h>
#include <UserInput_Server.h>
#include <Transform.h>
/*
void doom::physics::Picking::UpdatePicking()
{

	
	
}
*/

doom::physics::Ray doom::physics::Picking::GetCurrentCursorPointWorldRay()
{
	auto normalWorldPoint = Camera::GetMainCamera()->NDCToWorldPoint(Camera::GetMainCamera()->GetProjectionMatrix() *  -math::Vector3::forward); // In NDC coordinate, forward had positive z value, so put minus
	 
	//math::inverse(Camera::GetMainCamera()->GetViewMatrix()) * -math::Vector3::forward

	
	//auto normalWorldPoint = Camera::GetMainCamera()->GetTransform()->forward(); // In NDC coordinate, forward had positive z value, so put minus

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
