#pragma once

#include <vector>
#include <memory>

#include <Core.h>

#include "Scene.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class Scene;
	class Camera;
	class Entity;
	/// <summary>
	/// This class is same with SCENE in unity game engine
	/// </summary>
	class DOOM_API D_CLASS Scene : public DObject, public ISingleton<Scene>//, public GameFlow
	{
		GENERATE_BODY()


		friend class Entity;
		friend class GameCore;
		friend class graphics::Graphics_Server;

	private:

		D_PROPERTY(READONLY)
		size_t mEntityIDCounter{ 0 };

		D_PROPERTY(READONLY)
		std::vector<Entity*> mSpawnedEntityList{};
		Camera* mMainCamera{ nullptr };


		bool DestroyEntity_Internal(dooms::Entity* const entity) const;
		void InitializeEntity(dooms::Entity* const entity);

		void RemoveEntityFromSpawnedEntityLIst(dooms::Entity* const entity);

	protected:

		void FixedUpdateEntities();
		void UpdateEntities();
		void OnEndOfFrameOfEntities();
		

	public:

		Scene(std::string sceneName = "");

		Scene(const Scene&) = delete;
		Scene(Scene&&) noexcept = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) noexcept = delete;
		~Scene();

		static Scene* GetCurrentWorld();

		NO_DISCARD Entity* CreateNewEntity() noexcept;
		NO_DISCARD Entity* DuplicateEntity(const Entity* const copyedEntity) noexcept;
		NO_DISCARD static Entity* CreateNewEntityStatic() noexcept;
		NO_DISCARD static Entity* DuplicateEntityStatic(const Entity* const copyedEntity) noexcept;

		bool DestroyEntity(Entity& entity);
		void DestroyAllEntity();

		NO_DISCARD Camera* GetMainCamera() const;
		void SetMainCamera(Camera* camera);

		const std::vector<Entity*>& GetEntitiesInScene() const;
	};

}