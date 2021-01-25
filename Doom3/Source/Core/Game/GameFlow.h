#pragma once
#include "../Core.h"

namespace doom
{
	class GameCore;
	class GameFlow 
	{
		friend class GameCore;

	private:

		static void Init();
		

	public:
		
		
		static void Loop();
		
		GameFlow() = delete;
		GameFlow(const GameFlow&) = delete;
		GameFlow(GameFlow&&) = delete;
		GameFlow& operator=(const GameFlow&) = delete;
		GameFlow& operator=(GameFlow&&) = delete;
	};
}
