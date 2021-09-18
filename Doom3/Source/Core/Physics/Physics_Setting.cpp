#include "Physics_Setting.h"

#include <UI/PrintText.h>

void doom::physics::Physics_Setting::SetIsPhysicsOn(const bool isOn)
{
	Physics_Setting::bmIsPhysicsOn = isOn;

	if (Physics_Setting::bmIsPhysicsOn == true)
	{
		doom::ui::PrintText("Physics On");
	}
	else
	{
		doom::ui::PrintText("Physics Off");
	}

}
