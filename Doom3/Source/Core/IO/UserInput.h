#pragma once
#include "../Game/GameFlow.h"
#include "../../Helper/Singleton.h"

namespace doom
{
	namespace userinput
	{
		class UserInput : public GameFlow, public ISingleton<UserInput>
		{
		};

	}
}

