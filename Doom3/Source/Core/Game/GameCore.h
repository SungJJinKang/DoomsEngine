#pragma once
#include "../Core.h"


class IniData;

namespace Doom
{
	class Graphics;
	class GameFlow;

	class GameCore
	{
	private:
		static const char* configFilePath;
		static IniData ConfigData;

	public:
		friend class Graphics;

		static void Init();
		static bool Loop();
		
		
		
		GameCore() = delete;
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;
	};
}
