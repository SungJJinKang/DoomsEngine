#include "Physics_Setting.h"

#include <UI/PrintText.h>

void dooms::physics::Physics_Setting::SetIsPhysicsOn(const bool isOn)
{
	Physics_Setting::bmIsPhysicsOn = isOn;

	if (Physics_Setting::bmIsPhysicsOn == true)
	{
		dooms::ui::PrintText("Physics On");
	}
	else
	{
		dooms::ui::PrintText("Physics Off");
	}

}
