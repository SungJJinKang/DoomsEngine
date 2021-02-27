#include "Picking.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Camera.h>
#include <UserInput_Server.h>

void doom::physics::Picking::UpdatePicking()
{
	auto MouseNDCPosition = Camera::GetMainCamera()->ScreenToNDCPoint({ userinput::UserInput_Server::GetMouseScreenPositionX(), userinput::UserInput_Server::GetMouseScreenPositionY(), 0.0 });
	//D_DEBUG_LOG(MouseViewPortPosition.toString());
}

::doom::ColliderComponent* doom::physics::Picking::TryPicking(const math::Vector2 mousePoint)
{
	return nullptr;
}
