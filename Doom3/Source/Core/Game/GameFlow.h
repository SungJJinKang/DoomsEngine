#pragma once
#include "../../Helper/Singleton.h"


namespace Doom
{
	class GameCore;
	class GameFlow : public Singleton<GameFlow>
	{
	private:

		constexpr GameFlow()
		{

		}

		void Init();
		inline void Loop()
		{

		}
	public:
		friend class GameCore;
		

		

		GameFlow(const GameFlow&) = delete;
		GameFlow(GameFlow&&) = delete;
		GameFlow& operator=(const GameFlow&) = delete;
		GameFlow& operator=(GameFlow&&) = delete;
	};
}
