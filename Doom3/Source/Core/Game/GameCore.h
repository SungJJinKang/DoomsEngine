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

		std::unique_ptr<Scene> mCurrentScene{};
		std::unique_ptr<Scene> CreateNewScene(std::string sceneName = "");

		SharedScene mSharedWorld{};

		
	public:
		

		GameCore();
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;

		IniData& GetConfigData();


		virtual void Init() final;
		/// <summary>
		/// Frame Loop
		/// </summary>
		virtual void Update() final
		{
			this->mCurrentScene->UpdatePlainComponents();

			D_START_PROFILING("GraphicsUpdate", eProfileLayers::GPU);
			this->mGraphicsManager.Update();
			D_END_PROFILING("GraphicsUpdate");

			this->OnEndOfFrame();
		}

		virtual void OnEndOfFrame() final
		{
			this->mGraphicsManager.OnEndOfFrame();

			this->mCurrentScene->OnEndOfFrameOfEntities();
		}

	};
}
