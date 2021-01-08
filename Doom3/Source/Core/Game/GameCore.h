#pragma once
#include "../Core.h"

#include "../../Helper/Singleton.h"
#include "../../Helper/IniParser.h"

#include "GameFlow.h"




namespace Doom
{
	class Graphics;

	class GameCore : public Singleton<GameCore>
	{
	private:
		static const char* configFilePath;
		IniData initData;

		GameFlow gameFlow;

	public:
		friend class Graphics;
		GameCore() : initData{ IniParser::ParseIniFile(GET_RALATIVE_PATH("config.ini"))  }
		{

		}

		void Init();
		inline void Loop()
		{
			this->gameFlow.Loop();
		}
		

		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;
	};
}
