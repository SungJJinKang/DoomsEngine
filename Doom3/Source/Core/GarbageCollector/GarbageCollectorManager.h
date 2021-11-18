#pragma once

#include <Core.h>

#include <Game/IGameFlow.h>

namespace dooms
{
	namespace gc
	{
		class DOOM_API D_CLASS GarbageCollectorManager : public IGameFlow, public ISingleton<GarbageCollectorManager>
		{

		};
	}
	
}


