#include "RenderingAABBController.h"

#include "Graphics/Graphics_Setting.h"

void doom::RenderingAABBController::InitComponent()
{
}

void doom::RenderingAABBController::UpdateComponent()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F6))
	{
		doom::graphics::Graphics_Setting::mDrawRenderingBoundingBox = !doom::graphics::Graphics_Setting::mDrawRenderingBoundingBox;
	}
}

void doom::RenderingAABBController::OnEndOfFrame_Component()
{
}
