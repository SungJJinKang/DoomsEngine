#include "Physics_Setting.h"



void dooms::physics::Physics_Setting::SetIsPhysicsOn(const bool isOn)
{
	const bool isChanged = (Physics_Setting::bmIsPhysicsOn != isOn);

	Physics_Setting::bmIsPhysicsOn = isOn;

	if(isChanged == true)
	{
		if (Physics_Setting::bmIsPhysicsOn == true)
		{
			D_RELEASE_LOG(eLogType::D_LOG, "Physics On");
		}
		else
		{
			D_RELEASE_LOG(eLogType::D_LOG, "Physics Off");
		}
	}
	

}
