#pragma once
#include <vector>

namespace doom
{
	class Scene;
	class Entity;
	/// <summary>
	/// This class is same with scene in unity game engine
	/// </summary>
	class World
	{
	private:
		static inline World* mCurrentWorld{};
		std::vector<Entity*> mSpawnedEntities;
		World();
		~World();
	public:
		[[nodiscard]] static Entity& CreateNewEntity() noexcept;
		static bool DestroyEntity(Entity& entity);
	};

}