#include "Scene.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

#include "Entity.h"
#include <Rendering/Camera.h>
#include "ResourceManagement/Pool/ObjectPool.h"
#include "ResourceManagement/JobSystem_cpp/JobSystem.h"

using namespace doom;

Scene::Scene(std::string sceneName) 
{

}


Scene::~Scene()
{

}

[[nodiscard]] Entity* Scene::CreateNewEntity() noexcept
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD; // if you wanna createnewentity in subthread, you should 

	Entity* newEntity = CreateDObject<Entity>(mEntityIDCounter++, nullptr); // resource::ObjectPool<Entity>::AllocateFromPool(nullptr);
	mSpawnedEntities.emplace_back(newEntity);


	InitializeEntity(newEntity);

	return newEntity;
}

bool Scene::DestroyEntity(Entity& entity)
{
	bool isSuccess = false;

	size_t size = mSpawnedEntities.size();

	for (size_t i = 0; i < size; i++)
	{
		if (mSpawnedEntities[i].get() == &entity)
		{
			std::vector_swap_popback(mSpawnedEntities, mSpawnedEntities.begin() + i);
			isSuccess = true;
			break;
		}
	}

	return isSuccess;
}

doom::Scene* Scene::GetCurrentWorld()
{
	return GetSingleton();
}

void Scene::FixedUpdatePlainComponents()
{
	for (size_t i = 0; i < mSpawnedEntities.size(); i++)
	{
		mSpawnedEntities[i]->FixedUpdate_PlainComponent();
	}
}

void Scene::UpdatePlainComponents()
{
	for (size_t i = 0; i < mSpawnedEntities.size(); i++)
	{
		mSpawnedEntities[i]->Update_PlainComponent();
	}
}

void Scene::InitializeEntity(doom::Entity* const entity)
{
	entity->SetOwnerDObject(this);
}

void doom::Scene::OnEndOfFrameOfEntities()
{
	for (size_t i = 0; i < mSpawnedEntities.size(); i++)
	{
		mSpawnedEntities[i]->OnEndOfFramePlainComponentsAndEntity();
	}
}


[[nodiscard]] doom::Camera* Scene::GetMainCamera() const
{
	return mMainCamera;
}

void Scene::SetMainCamera(Camera* camera)
{
	mMainCamera = camera;
	if (mMainCamera != nullptr)
	{
		mMainCamera->SetDirtyTrueAtThisFrame(); // make dirty for update new projection
		mMainCamera->OnSetMainCamera();
	}
	
}
