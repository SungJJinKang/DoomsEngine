#include "World.h"

#include "Entity.h"
#include "../../Helper/vector_erase_move_lastelement/vector_swap_erase.h"
using namespace doom;

World::World() : mSpawnedEntities{}
{

}

World::~World()
{

}

[[nodiscard]] Entity& World::CreateNewEntity() noexcept
{
	Entity* newEntity = new Entity();
	World::mCurrentWorld->mSpawnedEntities.push_back(newEntity);
	return *newEntity;
}

bool World::DestroyEntity(Entity& entity)
{
	auto currentWorld = World::mCurrentWorld;
	size_t size = currentWorld->mSpawnedEntities.size();
	for (size_t i = 0; i < size; i++)
	{
		if (currentWorld->mSpawnedEntities[i] == &entity)
		{
			// if i is last element

			// if vector size size is less than 2
			delete World::mCurrentWorld->mSpawnedEntities[i];

			std::vector_swap_erase(currentWorld->mSpawnedEntities, i);
			
			
			return true;
		}
	}

	return false;
}
