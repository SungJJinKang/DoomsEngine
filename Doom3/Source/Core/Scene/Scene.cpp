#include "Scene.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

#include "Entity.h"
#include <Rendering/Camera.h>
#include "ResourceManagement/Pool/ObjectPool.h"
#include "ResourceManagement/JobSystem_cpp/JobSystem.h"

using namespace doom;

Scene::Scene(std::string sceneName) 
{

}


Scene::~Scene()
{
	DestroyAllEntity();
}

NO_DISCARD Entity* Scene::CreateNewEntity() noexcept
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD; // if you wanna createnewentity in subthread, you should 

	Entity* newEntity = CreateDObject<Entity>(mEntityIDCounter++, nullptr); // resource::ObjectPool<Entity>::AllocateFromPool(nullptr);

	D_ASSERT(newEntity != nullptr);

	mSpawnedEntities.emplace_back(newEntity);


	InitializeEntity(newEntity);

	return newEntity;
}

Entity* Scene::DuplicateEntity(const Entity* const copyedEntity) noexcept
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD; // if you wanna createnewentity in subthread, you should 

	Entity* newEntity = Scene::CreateNewEntity(); // resource::ObjectPool<Entity>::AllocateFromPool(nullptr);

	doom::Entity::CopyEntity(*copyedEntity, *newEntity);

	return newEntity;
}

Entity* Scene::CreateNewEntityStatic() noexcept
{
	return Scene::GetSingleton()->CreateNewEntity();
}

Entity* Scene::DuplicateEntityStatic(const Entity* const copyedEntity) noexcept
{
	return Scene::GetSingleton()->DuplicateEntity(copyedEntity);
}

bool Scene::DestroyEntity(Entity& entity)
{
	bool isSuccess = false;
	
	for ( std::ptrdiff_t i = mSpawnedEntities.size() - 1 ; i >= 0 ; i-- )
	{
		if (mSpawnedEntities[i] == &entity)
		{
			std::vector_swap_popback(mSpawnedEntities, mSpawnedEntities.begin() + i);
			DestroyEntity_Internal(&entity);
			isSuccess = true;
			break;
		}
	}

	return isSuccess;
}

void doom::Scene::DestroyAllEntity()
{
	for(doom::Entity* entity : mSpawnedEntities)
	{
		DestroyEntity_Internal(entity);
	}
	mSpawnedEntities.clear();
}

doom::Scene* Scene::GetCurrentWorld()
{
	return GetSingleton();
}

void Scene::FixedUpdatePlainComponents()
{
	for (size_t i = 0; i < mSpawnedEntities.size(); i++)
	{
		mSpawnedEntities[i]->FixedUpdate_PlainComponent();
	}
}

void Scene::UpdatePlainComponents()
{
	for (size_t i = 0; i < mSpawnedEntities.size(); i++)
	{
		mSpawnedEntities[i]->Update_PlainComponent();
	}
}

bool Scene::DestroyEntity_Internal(Entity* entity) const
{
	bool isSuccess = false;

	if(IsValid(entity) == true)
	{
		delete entity;
		isSuccess = true;
	}

	return isSuccess;
}

void Scene::InitializeEntity(doom::Entity* const entity)
{
	entity->SetOwnerDObject(this);
}

void doom::Scene::OnEndOfFrameOfEntities()
{
	for (size_t i = 0; i < mSpawnedEntities.size(); i++)
	{
		mSpawnedEntities[i]->OnEndOfFramePlainComponentsAndEntity();
	}
}


NO_DISCARD doom::Camera* Scene::GetMainCamera() const
{
	return mMainCamera;
}

void Scene::SetMainCamera(Camera* camera)
{
	mMainCamera = camera;
	if (mMainCamera != nullptr)
	{
		mMainCamera->SetDirtyTrueAtThisFrame(); // make dirty for update new projection
		mMainCamera->OnSetMainCamera();
	}
	
}
