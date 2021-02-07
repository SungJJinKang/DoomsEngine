#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"
namespace doom
{
	class Scene;
	/// <summary>
	/// This class is same with scene in unity game engine
	/// </summary>
	class World : ISingleton<World>, IGameFlow
	{
		friend class GameCore;
	private:
		std::vector<std::unique_ptr<Entity, Entity::Deleter>> mSpawnedEntities;
		World();
		
	public:
		~World();

		static World& GetCurrentWorld();

		[[nodiscard]] Entity& CreateNewEntity() noexcept;
		bool DestroyEntity(Entity& entity);

	protected:
		void Init() override;
		void Update() override;

	};

}