#pragma once

#include <vector>
#include <memory>

#include <Core.h>

namespace doom
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
	class DOOM_API Scene : public DObject, public ISingleton<Scene>//, public GameFlow
	{

		DOBJECT_CLASS_BODY(Scene, doom::eDOBJECT_ClassFlags::NonCopyable);
		DOBJECT_CLASS_BASE_CHAIN(DObject)

		friend class GameCore;
		friend class graphics::Graphics_Server;

	private:

		SIZE_T mEntityIDCounter{ 0 };
		std::vector<Entity*> mSpawnedEntities{};
		Camera* mMainCamera{ nullptr };


		bool DestroyEntity_Internal(Entity* entity) const;
		void InitializeEntity(doom::Entity* const entity);

	protected:

		void FixedUpdatePlainComponents();
		void UpdatePlainComponents();
		void OnEndOfFrameOfEntities();
		

	public:

		Scene(std::string sceneName = "");

		Scene(const Scene&) = delete;
		Scene(Scene&&) noexcept = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) noexcept = delete;
		~Scene();

		static Scene* GetCurrentWorld();

		[[nodiscard]] Entity* CreateNewEntity() noexcept;
		[[nodiscard]] Entity* DuplicateEntity(const Entity* const copyedEntity) noexcept;
		[[nodiscard]] static Entity* CreateNewEntityStatic() noexcept;
		[[nodiscard]] static Entity* DuplicateEntityStatic(const Entity* const copyedEntity) noexcept;

		bool DestroyEntity(Entity& entity);
		void DestroyAllEntity();

		[[nodiscard]] Camera* GetMainCamera() const;
		void SetMainCamera(Camera* camera);


	};

}