#pragma once
#include "../Core.h"
#include "IGameFlow.h"
#include "../../Helper/Singleton.h"
#include "../../Helper/SimpleIniParser.h"

#include <memory>


#include "AssetManager.h"

#include "../Scene/SharedScene.h"
#include "../Scene/Scene.h"

#include "../Graphics/Graphics_Server.h"
#include "../Physics/Physics_Server.h"
#include "../ResourceManagement/Thread_Server.h"
#include "../IO/UserInput_Server.h"
#include "../Time/Time_Server.h"

namespace doom
{

	class IGameFlow;

	class GameCore : public IGameFlow, public ISingleton<GameCore>
	{
		friend class graphics::Graphics_Server;
		friend class AssetManager;
	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		//Servers
		assetimporter::AssetManager mAssetManager{};
		graphics::Graphics_Server mGraphics_Server{};
		physics::Physics_Server mPhysics_Server{};
		resource::Thread_Server mThreadManager{};
		userinput::UserInput_Server mUserImput_Server{};
		time::Time_Server mTime_Server{};

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
			this->mTime_Server.Update();

			D_START_PROFILING("Update Physics", eProfileLayers::CPU);
			this->mPhysics_Server.Update();
			D_END_PROFILING("Update Physics");

			D_START_PROFILING("Process UserInput", eProfileLayers::CPU);
			this->mUserImput_Server.Update();
			D_END_PROFILING("Process UserInput");

			D_START_PROFILING("Update PlainComponents", eProfileLayers::CPU);
			this->mCurrentScene->UpdatePlainComponents();
			D_END_PROFILING("Update PlainComponents");

			D_START_PROFILING("GraphicsUpdate", eProfileLayers::GPU);
			this->mGraphics_Server.Update();
			D_END_PROFILING("GraphicsUpdate");
			

			this->OnEndOfFrame();
		}

		virtual void OnEndOfFrame() final
		{
			this->mTime_Server.OnEndOfFrame();

			this->mPhysics_Server.OnEndOfFrame();

			this->mUserImput_Server.OnEndOfFrame();

			this->mCurrentScene->OnEndOfFrameOfEntities();

			this->mGraphics_Server.OnEndOfFrame();

		}

	};
}
