#pragma once
#include "../Core.h"
#include "IGameFlow.h"
#include "../../Helper/Singleton.h"
#include "../../Helper/SimpleIniParser.h"

#include "../Graphics/Graphics.h"
#include "AssetManager.h"
#include "../ResourceManagement/ThreadManager.h"
#include "../CoreComponent/SharedWorld.h"


namespace doom
{

	class GameFlow;

	class GameCore : public IGameFlow, public ISingleton<GameCore>
	{
		friend class graphics::Graphics;
		friend class AssetManager;
	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		assetimporter::AssetManager mAssetManager{};
		graphics::Graphics mGraphics{};
		resource::ThreadManager mThreadManager{};
		SharedWorld mSharedWorld{};
	public:
		

		GameCore() = default;
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;

		IniData& GetConfigData();
	protected:

	public:
		virtual void Init() final;
		virtual void Update() final;

	};
}
