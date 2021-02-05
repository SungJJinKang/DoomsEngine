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
	Entity* newEntity = new Entity(nullptr);
	World::mCurrentWorld->mSpawnedEntities.emplace_back(newEntity);
	return *newEntity;
}

bool World::DestroyEntity(Entity& entity)
{
	auto currentWorld = World::mCurrentWorld;
	size_t size = currentWorld->mSpawnedEntities.size();
	for (size_t i = 0; i < size; i++)
	{
		if (currentWorld->mSpawnedEntities[i].get() == &entity)
		{
			std::vector_swap_erase(currentWorld->mSpawnedEntities, i);
			
			return true;
		}
	}

	return false;
}
