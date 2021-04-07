#include "Scene.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"

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

	Entity* newEntity = new Entity(mEntityIDCounter++, nullptr); // resource::ObjectPool<Entity>::AllocateFromPool(nullptr);
	this->mSpawnedEntities.emplace_back(newEntity);
	return newEntity;
}

bool Scene::DestroyEntity(Entity& entity)
{
	size_t size = this->mSpawnedEntities.size();

	Entity* pointer = &entity;
	delete pointer;

	for (size_t i = 0; i < size; i++)
	{
		if (this->mSpawnedEntities[i].get() == pointer)
		{
			std::vector_swap_popback(this->mSpawnedEntities, this->mSpawnedEntities.begin() + i);
			return true;
		}
	}

	return false;
}

doom::Scene* Scene::GetCurrentWorld()
{
	return GetSingleton();
}

void Scene::FixedUpdatePlainComponents()
{
	for (size_t i = 0; i < this->mSpawnedEntities.size(); i++)
	{
		this->mSpawnedEntities[i]->FixedUpdate_PlainComponent();
	}
}

void Scene::UpdatePlainComponents()
{
	for (size_t i = 0; i < this->mSpawnedEntities.size(); i++)
	{
		this->mSpawnedEntities[i]->Update_PlainComponent();
	}
}

void doom::Scene::OnEndOfFrameOfEntities()
{
	for (size_t i = 0; i < this->mSpawnedEntities.size(); i++)
	{
		this->mSpawnedEntities[i]->OnEndOfFramePlainComponentsAndEntity();
	}
}


[[nodiscard]] doom::Camera* Scene::GetMainCamera() const
{
	return this->mMainCamera;
}

void Scene::SetMainCamera(Camera* camera)
{
	this->mMainCamera = camera;
	if (this->mMainCamera != nullptr)
	{
		this->mMainCamera->SetDirtyTrueAtThisFrame(); // make dirty for update new projection
		this->mMainCamera->OnSetMainCamera();
	}
	
}
