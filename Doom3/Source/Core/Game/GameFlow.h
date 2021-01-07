#pragma once
#include "../../Helper/Singleton.h"

namespace Doom
{
	class GameFlow : public Singleton<GameFlow>
	{
	private:


	public:
		constexpr GameFlow()
		{

		}

		void Init();
		inline void Loop()
		{

		}

		GameFlow(const GameFlow&) = delete;
		GameFlow(GameFlow&&) = delete;
		GameFlow& operator=(const GameFlow&) = delete;
		GameFlow& operator=(GameFlow&&) = delete;
	};
}
