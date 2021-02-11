#pragma once
#include "../Game/IGameFlow.h"
#include "../../Helper/Singleton.h"

namespace doom
{
	namespace userinput
	{
		class UserInput : public IGameFlow, public ISingleton<UserInput>
		{
		};

	}
}

