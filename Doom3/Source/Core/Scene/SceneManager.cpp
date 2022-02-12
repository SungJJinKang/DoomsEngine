#include "SceneManager.h"

#include "Scene/Scene.h"

#define DEFAULT_SCENE_NAME "Scene"

dooms::SceneManager::SceneManager()
	: mCurrentScene(nullptr), mLayerManager()
{
}

dooms::SceneManager::~SceneManager()
{
	mCurrentScene->SetIsPendingKill();
}

void dooms::SceneManager::Init(const int argc, char* const* const argv)
{
	mLayerManager.Initialize();
}

void dooms::SceneManager::LateInit()
{
	IGameFlow::LateInit();
	mCurrentScene = CreateNewScene();
	D_ASSERT(IsValid(mCurrentScene));
}

void dooms::SceneManager::Update()
{
	mCurrentScene->UpdateEntities(); // Update plain Components ( Game Logic )
}

void dooms::SceneManager::FixedUpdate()
{
	IGameFlow::FixedUpdate();
	mCurrentScene->FixedUpdateEntities(); // Update plain Components ( Game Logic )
}

void dooms::SceneManager::OnEndOfFrame()
{
	mCurrentScene->OnEndOfFrameOfEntities();
}

dooms::Scene* dooms::SceneManager::CreateNewScene()
{
	 return CreateNewScene(DEFAULT_SCENE_NAME);
}

dooms::Scene* dooms::SceneManager::CreateNewScene(const std::string& sceneName)
{
	return dooms::CreateDObject<Scene>(sceneName);
}

void dooms::SceneManager::OnSetPendingKill()
{
	IGameFlow::OnSetPendingKill();

	mCurrentScene->SetIsPendingKill();
}
