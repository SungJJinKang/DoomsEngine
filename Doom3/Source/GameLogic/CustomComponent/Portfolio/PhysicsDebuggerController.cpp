#include "PhysicsDebuggerController.h"

#include <Physics/Physics_Setting.h>

void dooms::PhysicsDebuggerController::InitComponent()
{
    dooms::physics::Physics_Setting::SetIsPhysicsOn(false);
    dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = false;
}

void dooms::PhysicsDebuggerController::UpdateComponent()
{
	if(entity != nullptr)
	{

		entity->GetTransform()->SetPosition(GetTransform()->GetPosition() + GetTransform()->forward().normalized() * 50);
	}

    if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7))
    {
        dooms::physics::Physics_Setting::SetIsPhysicsOn(!dooms::physics::Physics_Setting::GetIsPhysicsOn());
    }

    if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8))
    {
        dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = !(dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER);
    }
}
