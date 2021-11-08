#pragma once
#include "IGameFlow.h"

#include <memory>


#include "AssetManager/AssetManager.h"

#include "../Scene/SharedScene.h"
#include "../Scene/Scene.h"

#include "ConfigData.h"

#include "../Graphics/Graphics_Server.h"
#include "../Physics/Physics_Server.h"
#include "../ResourceManagement/JobSystem_cpp/JobSystem.h"
#include "../IO/UserInput_Server.h"
#include "../Time/Time_Server.h"
#include "../DObject/Reflection/ReflectionManager.h"

namespace dooms
{

	class IGameFlow;

	class DOOM_API D_CLASS GameCore : public IGameFlow, public ISingleton<GameCore>
	{
		DOBJECT_CLASS_BODY(GameCore, dooms::eDOBJECT_ClassFlags::NonCopyable);
		DOBJECT_CLASS_BASE_CHAIN(IGameFlow)
	private:
		
		// Then, non-static data members are initialized in the order they were declared 
		// in the class definition (again regardless of the order of the mem-initializers).

		D_PROPERTY()
		INT32 ITERATION_PER_SECOND{};

		D_PROPERTY()
		INT32 TARGET_FRAME_RATE{};

		/// <summary>
		/// check this : https://github.com/godotengine/godot/blob/master/core/os/os.cpp -> add_frame_delay function
		/// </summary>
		D_PROPERTY()
		INT32	FRAME_DELAY_MILLISECOND{};

		D_PROPERTY()
		FLOAT32 FIXED_TIME_STEP{};

		D_PROPERTY()
		INT32 MAX_PHYSICS_STEP{ 8 };

		//Servers
		assetImporter::AssetManager mAssetManager{};
		graphics::Graphics_Server mGraphics_Server{};
		physics::Physics_Server mPhysics_Server{};
		resource::JobSystem mJobSystem{};
		userinput::UserInput_Server mUserImput_Server{};
		time::Time_Server mTime_Server{};
		reflection::ReflectionManager mReflectionManager{};

		std::unique_ptr<Scene> mCurrentScene{};
		std::unique_ptr<Scene> CreateNewScene(std::string sceneName = "");

		SharedScene mSharedWorld{};

		void InitGameSetting();
		
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
