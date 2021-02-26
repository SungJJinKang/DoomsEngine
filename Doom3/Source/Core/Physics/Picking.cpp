#include "Picking.h"
#include <PhysicsComponent/Collider.h>
#include <Camera.h>
#include <UserInput_Server.h>

#include <UserInput_Server.h>

void doom::physics::Picking::UpdatePicking()
{
	userinput::UserInput_Server::SetIsCursorVisible(true);
	userinput::UserInput_Server::SetIsCursorLockedInScreen(false);
	auto MouseViewPortPosition = Camera::GetMainCamera()->ScreenToNDCPoint({ userinput::UserInput_Server::GetMouseScreenPositionX(), userinput::UserInput_Server::GetMouseScreenPositionY(), 0.0 });
	//D_DEBUG_LOG(MouseViewPortPosition.toString());
}

::doom::Collider* doom::physics::Picking::TryPicking(const math::Vector2 mousePoint)
{
	return nullptr;
}
