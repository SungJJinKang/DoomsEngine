#pragma once
#include "../Core.h"
#include "GameFlow.h"
#include "../../Helper/Singleton.h"
#include "../../Helper/SimpleIniParser.h"

#include <memory>
#include "../Graphics/GraphicsManager.h"
#include "AssetManager.h"
#include "../ResourceManagement/ThreadManager.h"
#include "../Scene/SharedScene.h"
#include "../Scene/Scene.h"


namespace doom
{

	class GameFlow;

	class GameCore : public GameFlow, public ISingleton<GameCore>
	{
		friend class graphics::GraphicsManager;
		friend class AssetManager;
	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		//Servers
		assetimporter::AssetManager mAssetManager{};
		graphics::GraphicsManager mGraphicsManager{};
		resource::ThreadManager mThreadManager{};


		std::unique_ptr<Scene> mCurrentScene;
		SharedScene mSharedWorld{};
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
		virtual void OnEndOfFrame() final;
	};
}
