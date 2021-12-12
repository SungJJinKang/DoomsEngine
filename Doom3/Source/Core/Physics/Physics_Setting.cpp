#include "Physics_Setting.h"

#include <EngineGUI/PrintText.h>

void dooms::physics::Physics_Setting::SetIsPhysicsOn(const bool isOn)
{
	const bool isChanged = (Physics_Setting::bmIsPhysicsOn != isOn);

	Physics_Setting::bmIsPhysicsOn = isOn;

	if(isChanged == true)
	{
		if (Physics_Setting::bmIsPhysicsOn == true)
		{
			dooms::ui::PrintText("Physics On");
		}
		else
		{
			dooms::ui::PrintText("Physics Off");
		}
	}
	

}
