#pragma once
#include "../Core.h"
#include "IGameFlow.h"
#include "../../Helper/SimpleIniParser.h"

#include <memory>


#include "AssetManager/AssetManager.h"

#include "../Scene/SharedScene.h"
#include "../Scene/Scene.h"

#include "ConfigData.h"

#include "../OS/OS_Server.h"
#include "../Graphics/Graphics_Server.h"
#include "../Physics/Physics_Server.h"
#include "../ResourceManagement/JobSystem.h"
#include "../IO/UserInput_Server.h"
#include "../Time/Time_Server.h"
#include "../Time/MainTimer.h"

namespace doom
{

	class IGameFlow;

	class GameCore : public IGameFlow, public ISingleton<GameCore>
	{
		friend class graphics::Graphics_Server;
		friend class AssetManager;
	private:
		
		// Then, non-static data members are initialized in the order they were declared 
		// in the class definition (again regardless of the order of the mem-initializers).

		int ITERATION_PER_SECOND{};
		int TARGET_FRAME_RATE{};
		/// <summary>
		/// check this : https://github.com/godotengine/godot/blob/master/core/os/os.cpp -> add_frame_delay function
		/// </summary>
		int	FRAME_DELAY_MILLISECOND{};

		ConfigData mMainConfigData{};

		//Servers
		OS_Server mOS_Server{};
		assetimporter::AssetManager mAssetManager{};
		graphics::Graphics_Server mGraphics_Server{};
		physics::Physics_Server mPhysics_Server{};
		resource::JobSystem mJobSystem{};
		userinput::UserInput_Server mUserImput_Server{};
		time::Time_Server mTime_Server{};

		std::unique_ptr<Scene> mCurrentScene{};
		std::unique_ptr<Scene> CreateNewScene(std::string sceneName = "");

		SharedScene mSharedWorld{};

		void InitGameSetting() ;

		void UpdateGameCore();
		
	public:
		


		GameCore();
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;


		virtual void Init() final;
		virtual void LateInit() final;

		/// <summary>
		/// Frame Loop
		/// </summary>
		inline virtual void Update() final
		{
			this->UpdateGameCore();

			this->mTime_Server.Update_Internal();
			this->mTime_Server.Update();

			this->mJobSystem.Update_Internal();
			this->mJobSystem.Update();

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

			D_START_PROFILING("GraphicsUpdate", eProfileLayers::CPU);
			this->mGraphics_Server.Update_Internal();
			this->mGraphics_Server.Update();
			D_END_PROFILING("GraphicsUpdate");
		}

		/// <summary>
		/// Fixed Update may be called more than once per frame 
		/// if the fixed time step is less than the actual frame update time
		/// </summary>
		inline virtual void FixedUpdate() final
		{
			D_START_PROFILING("FixedUpdate_Internal Physics", eProfileLayers::CPU);
			this->mPhysics_Server.FixedUpdate_Internal();
			D_END_PROFILING("FixedUpdate_Internal Physics");

			D_START_PROFILING("FixedUpdate Physics", eProfileLayers::CPU);
			this->mPhysics_Server.FixedUpdate();
			D_END_PROFILING("FixedUpdate Physics");

			D_START_PROFILING("FixedUpdate PlainComponents", eProfileLayers::CPU);
			this->mCurrentScene->FixedUpdatePlainComponents(); // Update plain Components ( Game Logic )
			D_END_PROFILING("FixedUpdate PlainComponents");
		}

		inline virtual void OnEndOfFrame() final
		{
			this->mTime_Server.OnEndOfFrame_Internal();
			this->mTime_Server.OnEndOfFrame();

			this->mJobSystem.OnEndOfFrame_Internal();
			this->mJobSystem.OnEndOfFrame();

			this->mPhysics_Server.OnEndOfFrame_Internal();
			this->mPhysics_Server.OnEndOfFrame();

			this->mUserImput_Server.OnEndOfFrame_Internal();
			this->mUserImput_Server.OnEndOfFrame();

			this->mCurrentScene->OnEndOfFrameOfEntities(); // Update Plain Components ( Game Logic )

			this->mGraphics_Server.OnEndOfFrame_Internal();
			this->mGraphics_Server.OnEndOfFrame();

		}

		inline bool Tick()
		{
			
			D_START_PROFILING("Fixed Update", eProfileLayers::CPU);
			MainTimer::ResetFixedTimer();
			int fixedUpdateCount{ 0 };
			for (int i = 0; i < this->mPhysics_Server.MAX_PHYSICS_STEP; ++i)
			{
				fixedUpdateCount++;
				this->FixedUpdate();
				MainTimer::UpdateFixedTimer();
				if (MainTimer::GetFixedDeltaTime() > this->mPhysics_Server.FIXED_TIME_STEP)
				{
					break;
				}
			}
			D_END_PROFILING("Fixed Update");
			

			MainTimer::UpdateFrameTimer();
			
			D_START_PROFILING("Update", eProfileLayers::CPU);
			this->Update();
			D_END_PROFILING("Update");
			
			
			D_START_PROFILING("OnEndOfFrame", eProfileLayers::CPU);
			this->OnEndOfFrame();
			D_END_PROFILING("OnEndOfFrame");
			
			return true;
		}
		

		

		/// <summary>
		/// Clean Game Resources
		/// </summary>
		void CleanUp();







		
	};
}
