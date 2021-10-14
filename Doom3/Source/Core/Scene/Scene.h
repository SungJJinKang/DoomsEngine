#pragma once

#include <vector>
#include <memory>

#include <Core.h>
#include "Entity.h"

namespace doom
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class Scene;
	class Camera;
	/// <summary>
	/// This class is same with SCENE in unity game engine
	/// </summary>
	class DOOM_API Scene : public DObject, public ISingleton<Scene>//, public GameFlow
	{

		friend class GameCore;
		friend class graphics::Graphics_Server;

	private:

		SIZE_T mEntityIDCounter{ 0 };
		std::vector<std::unique_ptr<Entity, Entity::Deleter>> mSpawnedEntities{};
		Camera* mMainCamera{ nullptr };

		Scene(std::string sceneName = "");

		Scene(const Scene&) = delete;
		Scene(Scene&&) noexcept = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) noexcept = delete;

		void InitializeEntity(doom::Entity* const entity);

	protected:

		void FixedUpdatePlainComponents();
		void UpdatePlainComponents();
		void OnEndOfFrameOfEntities();
		

	public:

		~Scene();

		static Scene* GetCurrentWorld();

		[[nodiscard]] Entity* CreateNewEntity() noexcept;
		bool DestroyEntity(Entity& entity);
		void DestroyAllEntity();

		[[nodiscard]] Camera* GetMainCamera() const;
		void SetMainCamera(Camera* camera);


	};

}