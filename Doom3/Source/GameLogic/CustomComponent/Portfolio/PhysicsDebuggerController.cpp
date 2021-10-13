#include "PhysicsDebuggerController.h"

#include <Physics/Physics_Setting.h>

void doom::PhysicsDebuggerController::InitComponent()
{
    doom::physics::Physics_Setting::SetIsPhysicsOn(false);
    doom::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = false;
}

void doom::PhysicsDebuggerController::UpdateComponent()
{
	if(entity != nullptr)
	{

		entity->GetTransform()->SetPosition(GetTransform()->GetPosition() + GetTransform()->forward().normalized() * 50);
	}

    if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F7))
    if (entity != nullptr)
    {
        doom::physics::Physics_Setting::SetIsPhysicsOn(!doom::physics::Physics_Setting::GetIsPhysicsOn());
    }

    if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_F8))
    {
        doom::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = !(doom::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER);
    }
}
