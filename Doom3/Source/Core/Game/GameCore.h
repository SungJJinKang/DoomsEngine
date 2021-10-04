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
		~GameCore();

		virtual void Init() final;
		void InitServers();
		virtual void LateInit() final;

		/// <summary>
		/// Frame Loop
		/// </summary>
		virtual void Update() final;
		/// <summary>
		/// Fixed Update may be called more than once per frame 
		/// if the fixed time step is less than the actual frame update time
		/// </summary>
		virtual void FixedUpdate() final;
		virtual void OnEndOfFrame() final;
		bool Tick();
		

		

		/// <summary>
		/// Clean Game Resources
		/// </summary>
		void CleanUp();







		
	};
}
