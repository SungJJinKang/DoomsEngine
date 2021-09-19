#include "Picking.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Rendering/Camera.h>
#include <UserInput_Server.h>
#include <Transform.h>

#include <UI/PrintText.h>
doom::physics::Ray doom::physics::Picking::GetCurrentCursorPointWorldRay()
{
	const math::Vector3 currentNDCCursorPoint{ userinput::UserInput_Server::GetCurrentMouseNDCPosition() };
	
	const math::Vector3 cursorWorldCursorPoint = Camera::GetMainCamera()->NDCToWorldPoint(currentNDCCursorPoint); // In NDC coordinate, forward had positive z value, so put minus

	return physics::Ray(cursorWorldCursorPoint, cursorWorldCursorPoint - Camera::GetMainCamera()->GetTransform()->GetPosition());

}
