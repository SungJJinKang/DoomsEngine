#pragma once
#include "../Game/IGameFlow.h"
#include "../../Helper/Singleton.h"

#include "Phycis_Core.h"

namespace doom
{
	namespace physics
	{
		class Physics : public IGameFlow, public ISingleton<Physics>
		{
		};
	}
}


