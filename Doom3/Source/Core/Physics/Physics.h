#pragma once
#include "../Game/GameFlow.h"
#include "../../Helper/Singleton.h"

#include "Phycis_Core.h"

namespace doom
{
	namespace physics
	{
		class Physics : public GameFlow, public ISingleton<Physics>
		{
		};
	}
}


