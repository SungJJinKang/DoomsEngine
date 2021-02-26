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


		float mFixedTimeStep{};

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

		void InitGameSetting() ;
		
	public:
		

		GameCore();
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;

		const IniData& GetConfigData() const;


		virtual void Init() final;
		virtual void LateInit() final;

		bool Tick()
		{
			this->FixedUpdated();

			this->Update();

			this->OnEndOfFrame();

			return true;
		}
		

		virtual void OnEndOfFrame() final
		{
			this->mTime_Server.OnEndOfFrame_Internal();
			this->mTime_Server.OnEndOfFrame();
			
			this->mThreadManager.OnEndOfFrame_Internal();
			this->mThreadManager.OnEndOfFrame();

			this->mPhysics_Server.OnEndOfFrame_Internal();
			this->mPhysics_Server.OnEndOfFrame();

			this->mUserImput_Server.OnEndOfFrame_Internal();
			this->mUserImput_Server.OnEndOfFrame();

			this->mCurrentScene->OnEndOfFrameOfEntities(); // Update Plain Components ( Game Logic )

			this->mGraphics_Server.OnEndOfFrame_Internal();
			this->mGraphics_Server.OnEndOfFrame();

		}

		/// <summary>
		/// Clean Game Resources
		/// </summary>
		void CleanUp();







		/// <summary>
		/// Frame Loop
		/// </summary>
		virtual void Update() final
		{
			this->mTime_Server.Update_Internal();
			this->mTime_Server.Update();

			this->mThreadManager.Update_Internal();
			this->mThreadManager.Update();

			D_START_PROFILING("Update Physics", eProfileLayers::CPU);
			this->mPhysics_Server.Update_Internal();
			this->mPhysics_Server.Update();
			D_END_PROFILING("Update Physics");

			D_START_PROFILING("Process UserInput", eProfileLayers::CPU);
			this->mUserImput_Server.Update_Internal();
			this->mUserImput_Server.Update();
			D_END_PROFILING("Process UserInput");

			D_START_PROFILING("Update PlainComponents", eProfileLayers::CPU);
			this->mCurrentScene->UpdatePlainComponents(); // Update plain Components ( Game Logic )
			D_END_PROFILING("Update PlainComponents");

			D_START_PROFILING("GraphicsUpdate", eProfileLayers::GPU);
			this->mGraphics_Server.Update_Internal();
			this->mGraphics_Server.Update();
			D_END_PROFILING("GraphicsUpdate");
		}

		/// <summary>
		/// Fixed Update may be called more than once per frame 
		/// if the fixed time step is less than the actual frame update time
		/// </summary>
		virtual void FixedUpdated() final
		{
			D_START_PROFILING("FixedUpdate Physics", eProfileLayers::CPU);
			this->mPhysics_Server.FixedUpdate_Internal();
			this->mPhysics_Server.FixedUpdated();
			D_END_PROFILING("FixedUpdate Physics");
		}
	};
}
