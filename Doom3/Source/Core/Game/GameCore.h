#pragma once
#include "../Core.h"
#include "GameFlow.h"

class IniData;

namespace doom
{
	namespace graphics 
	{
		class Graphics;
	}

	class GameFlow;

	class GameCore
	{
	private:
		static const char* configFilePath;
		static IniData ConfigData;

	public:
		friend class ::doom::graphics::Graphics;

		static void Init();
		
		
		
		GameCore() = delete;
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;
	};
}
