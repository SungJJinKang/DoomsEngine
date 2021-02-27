#include "Scene.h"

#include "Entity.h"
#include "../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"
#include "../../Component/Camera.h"
using namespace doom;

Scene::Scene(std::string sceneName) 
{

}


Scene::~Scene()
{

}

[[nodiscard]] Entity* Scene::CreateNewEntity() noexcept
{
	Entity* newEntity = new Entity(nullptr);
	this->mSpawnedEntities.emplace_back(newEntity);
	return newEntity;
}

bool Scene::DestroyEntity(Entity& entity)
{
	size_t size = this->mSpawnedEntities.size();
	for (size_t i = 0; i < size; i++)
	{
		if (this->mSpawnedEntities[i].get() == &entity)
		{
			std::vector_swap_erase(this->mSpawnedEntities, i);
			
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
	for (auto& spawnedEntity : this->mSpawnedEntities)
	{
		spawnedEntity->FixedUpdate_PlainComponent();
	}
}

void Scene::UpdatePlainComponents()
{
	for (auto& spawnedEntity : this->mSpawnedEntities)
	{
		spawnedEntity->Update_PlainComponent();
	}
}

void doom::Scene::OnEndOfFrameOfEntities()
{
	for (auto& spawnedEntity : this->mSpawnedEntities)
	{
		spawnedEntity->OnEndOfFramePlainComponentsAndEntity();
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
