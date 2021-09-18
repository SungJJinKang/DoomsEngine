#pragma once
#include "../Core.h"
#include "IGameFlow.h"
#include "../../Helper/SimpleIniParser.h"

#include <memory>


#include "AssetManager/AssetManager.h"

#include "../Scene/SharedScene.h"
#include "../Scene/Scene.h"

#include "ConfigData.h"

#include "../OS/OS.h"
#include "../Graphics/Graphics_Server.h"
#include "../Physics/Physics_Server.h"
#include "../ResourceManagement/JobSystem_cpp/JobSystem.h"
#include "../IO/UserInput_Server.h"
#include "../Time/Time_Server.h"
#include "../Time/MainTimer.h"

namespace doom
{

	class IGameFlow;

	class GameCore : public IGameFlow, public ISingleton<GameCore>
	{
	private:
		
		// Then, non-static data members are initialized in the order they were declared 
		// in the class definition (again regardless of the order of the mem-initializers).

		int ITERATION_PER_SECOND{};
		int TARGET_FRAME_RATE{};
		/// <summary>
		/// check this : https://github.com/godotengine/godot/blob/master/core/os/os.cpp -> add_frame_delay function
		/// </summary>
		int	FRAME_DELAY_MILLISECOND{};
		float FIXED_TIME_STEP{};
		int MAX_PHYSICS_STEP{ 8 };

		//Servers
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
		
		ConfigData mGameConfigData{};

		GameCore();
		GameCore(const GameCore&) = delete;
		GameCore(GameCore&&) = delete;
		GameCore& operator=(const GameCore&) = delete;
		GameCore& operator=(GameCore&&) = delete;


		virtual void Init() final;
		void InitServers();
		virtual void LateInit() final;

		/// <summary>
		/// Frame Loop
		/// </summary>
		FORCE_INLINE virtual void Update() final
		{
			UpdateGameCore();

			D_START_PROFILING("mTime_Server.Update_Internal", eProfileLayers::CPU);
			mTime_Server.Update_Internal();
			mTime_Server.Update();
			D_END_PROFILING("mTime_Server.Update_Internal");

			D_START_PROFILING("mPhysics_Server.Update", eProfileLayers::CPU);
			mPhysics_Server.Update_Internal();
			mPhysics_Server.Update();
			D_END_PROFILING("mPhysics_Server.Update");

			D_START_PROFILING("mUserImput_Server.Update", eProfileLayers::CPU);
			mUserImput_Server.Update_Internal();
			mUserImput_Server.Update();
			D_END_PROFILING("mUserImput_Server.Update");

			D_START_PROFILING("mCurrentScene->UpdatePlainComponents", eProfileLayers::CPU);
			mCurrentScene->UpdatePlainComponents(); // Update plain Components ( Game Logic )
			D_END_PROFILING("mCurrentScene->UpdatePlainComponents");

			D_START_PROFILING("mGraphics_Server.Update", eProfileLayers::CPU);
			mGraphics_Server.Update_Internal();
			mGraphics_Server.Update();
			D_END_PROFILING("mGraphics_Server.Update");
		}

		/// <summary>
		/// Fixed Update may be called more than once per frame 
		/// if the fixed time step is less than the actual frame update time
		/// </summary>
		FORCE_INLINE virtual void FixedUpdate() final
		{
			D_START_PROFILING("mPhysics_Server.FixedUpdate_Internal", eProfileLayers::CPU);
			mPhysics_Server.FixedUpdate_Internal();
			D_END_PROFILING("mPhysics_Server.FixedUpdate_Internal");

			D_START_PROFILING("mPhysics_Server.FixedUpdate", eProfileLayers::CPU);
			mPhysics_Server.FixedUpdate();
			D_END_PROFILING("mPhysics_Server.FixedUpdate");

			D_START_PROFILING("mCurrentScene->FixedUpdatePlainComponents", eProfileLayers::CPU);
			mCurrentScene->FixedUpdatePlainComponents(); // Update plain Components ( Game Logic )
			D_END_PROFILING("mCurrentScene->FixedUpdatePlainComponents");
		}

		FORCE_INLINE virtual void OnEndOfFrame() final
		{
			D_START_PROFILING("mTime_Server OnEndOfFrame", eProfileLayers::CPU);
			mTime_Server.OnEndOfFrame_Internal();
			mTime_Server.OnEndOfFrame();
			D_END_PROFILING("mTime_Server OnEndOfFrame");

			D_START_PROFILING("mPhysics_Server OnEndOfFrame", eProfileLayers::CPU);
			mPhysics_Server.OnEndOfFrame_Internal();
			mPhysics_Server.OnEndOfFrame();
			D_END_PROFILING("mPhysics_Server OnEndOfFrame");

			D_START_PROFILING("mUserImput_Server OnEndOfFrame", eProfileLayers::CPU);
			mUserImput_Server.OnEndOfFrame_Internal();
			mUserImput_Server.OnEndOfFrame();
			D_END_PROFILING("mUserImput_Server OnEndOfFrame");

			D_START_PROFILING("mCurrentScene OnEndOfFrame", eProfileLayers::CPU);
			mCurrentScene->OnEndOfFrameOfEntities(); // Update Plain Components ( Game Logic )
			D_END_PROFILING("mCurrentScene OnEndOfFrame");

			D_START_PROFILING("mGraphics_Server OnEndOfFrame", eProfileLayers::CPU);
			mGraphics_Server.OnEndOfFrame_Internal();
			mGraphics_Server.OnEndOfFrame();
			D_END_PROFILING("mGraphics_Server OnEndOfFrame");
		}

		FORCE_INLINE bool Tick()
		{
			
			D_START_PROFILING("Fixed Update", eProfileLayers::CPU);
			MainTimer::ResetFixedTimer();
			int fixedUpdateCount{ 0 };
			for (int i = 0; i < MAX_PHYSICS_STEP; ++i)
			{
				fixedUpdateCount++;
				FixedUpdate();
				MainTimer::UpdateFixedTimer();
				if (MainTimer::GetFixedDeltaTime() > FIXED_TIME_STEP)
				{
					break;
				}
			}
			D_END_PROFILING("Fixed Update");
			

			MainTimer::UpdateFrameTimer();
			
			D_START_PROFILING("Update", eProfileLayers::CPU);
			Update();
			D_END_PROFILING("Update");
			
			
			D_START_PROFILING("OnEndOfFrame", eProfileLayers::CPU);
			OnEndOfFrame();
			D_END_PROFILING("OnEndOfFrame");
			
			return true;
		}
		

		

		/// <summary>
		/// Clean Game Resources
		/// </summary>
		void CleanUp();







		
	};
}
