#pragma once

#include <Core.h>
#include <Game/IGameFlow.h>
#include "Layer/LayerManager.h"

#include "SceneManager.reflection.h"
namespace dooms
{
	class Scene;
	class D_CLASS SceneManager : public IGameFlow
	{
		GENERATE_BODY()

	private:


		D_PROPERTY()
		Scene* mCurrentScene;
		
		D_PROPERTY()
		LayerManager mLayerManager;

	public:

		SceneManager();
		~SceneManager();

		void Init(const int argc, char* const* const argv) override;
		void LateInit() override;
		void Update() override;
		void FixedUpdate() override;
		void OnEndOfFrame() override;

		dooms::Scene* CreateNewScene();
		dooms::Scene* CreateNewScene(const std::string& sceneName);
		
	};
}


