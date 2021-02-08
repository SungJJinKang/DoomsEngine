#include "World.h"

#include "Entity.h"
#include "../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"
#include "../../Component/Camera.h"
using namespace doom;

World::World() : mSpawnedEntities{}
{

}

World::~World()
{

}

[[nodiscard]] Entity& World::CreateNewEntity() noexcept
{
	Entity* newEntity = new Entity(nullptr);
	this->mSpawnedEntities.emplace_back(newEntity);
	return *newEntity;
}

bool World::DestroyEntity(Entity& entity)
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

doom::World* World::GetCurrentWorld()
{
	return GetSingleton();
}

void World::Init()
{
}

void World::Update()
{
}


doom::Camera* World::GetMainCamera() const
{
	return this->mMainCamera;
}

void World::SetMainCamera(Camera* camera)
{
	this->mMainCamera = camera;
	if (this->mMainCamera != nullptr)
	{
		this->mMainCamera->bmIsDirty = true; // make dirty for update new projection
	}
	
}
