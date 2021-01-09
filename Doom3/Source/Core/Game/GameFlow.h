#pragma once
#include "../Core.h"

namespace Doom
{
	class GameCore;
	class GameFlow 
	{
	private:

	

		static void Init();
		static bool Loop();
	public:
		friend class GameCore;
		

		
		GameFlow() = delete;
		GameFlow(const GameFlow&) = delete;
		GameFlow(GameFlow&&) = delete;
		GameFlow& operator=(const GameFlow&) = delete;
		GameFlow& operator=(GameFlow&&) = delete;
	};
}
