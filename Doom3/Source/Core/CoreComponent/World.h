#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
namespace doom
{
	class Scene;
	/// <summary>
	/// This class is same with scene in unity game engine
	/// </summary>
	class World
	{
	private:
		static inline World* mCurrentWorld{};
		std::vector<std::unique_ptr<Entity, Entity::Deleter>> mSpawnedEntities;
		World();
		~World();
	public:
		[[nodiscard]] static Entity& CreateNewEntity() noexcept;
		static bool DestroyEntity(Entity& entity);
	};

}