#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "../Game/IGameFlow.h"
#include "SharedWorldSetting.h"
#include "../Graphics/GraphicsInWorld.h"

namespace doom
{
	class Scene;
	class Camera;
	/// <summary>
	/// This class is same with SCENE in unity game engine
	/// </summary>
	class World : public ISingleton<World>, public IGameFlow
	{
		friend class GameCore;
	private:
		World();

		World(const World&) = delete;
		World(World&&) noexcept = delete;
		World& operator=(const World&) = delete;
		World& operator=(World&&) noexcept = delete;


		std::vector<std::unique_ptr<Entity, Entity::Deleter>> mSpawnedEntities;
		Camera* mMainCamera{ nullptr };

		graphics::GraphicsInWorld mGraphicsInWorld{};
		

	public:

		~World();

		static World* GetCurrentWorld();

		[[nodiscard]] Entity& CreateNewEntity() noexcept;
		bool DestroyEntity(Entity& entity);

		Camera* GetMainCamera() const;
		void SetMainCamera(Camera* camera);

	protected:
		void Init() override;
		void Update() override;

	};

}