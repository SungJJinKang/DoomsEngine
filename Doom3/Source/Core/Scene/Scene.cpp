#include "Scene.h"

#include "../../Helper/vector_erase_move_lastelement/vector_swap_popback.h"

#include "Entity.h"
#include <Rendering/Camera.h>
#include "ResourceManagement/Pool/ObjectPool.h"
#include "ResourceManagement/JobSystem_cpp/JobSystem.h"

using namespace dooms;

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

	mSpawnedEntityList.emplace_back(newEntity);


	InitializeEntity(newEntity);

	return newEntity;
}

Entity* Scene::DuplicateEntity(const Entity* const copyedEntity) noexcept
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD; // if you wanna createnewentity in subthread, you should 

	D_ASSERT(IsValid(copyedEntity) == true);
	Entity* newEntity = nullptr;

	if(IsValid(copyedEntity) == true)
	{
		newEntity = Scene::CreateNewEntity(); // resource::ObjectPool<Entity>::AllocateFromPool(nullptr);

		dooms::Entity::CopyEntity(*copyedEntity, *newEntity);
	}
	
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
	
	for ( std::ptrdiff_t i = mSpawnedEntityList.size() - 1 ; i >= 0 ; i-- )
	{
		if (mSpawnedEntityList[i] == &entity)
		{
			swap_popback::vector_swap_popback(mSpawnedEntityList, mSpawnedEntityList.begin() + i);
			entity.DestroyEntitySelf();
			isSuccess = true;
			break;
		}
	}

	return isSuccess;
}

void dooms::Scene::DestroyAllEntity()
{
	std::vector<dooms::Entity*> spawnedEntities = mSpawnedEntityList; // to prevent bugs from entity is erased from mSpawnedEntityList for looping
	for(dooms::Entity* entity : spawnedEntities)
	{
		if (IsValid(entity) == true)
		{
			entity->DestroyEntitySelf();
		}
	}
	mSpawnedEntityList.clear();
}

dooms::Scene* Scene::GetCurrentWorld()
{
	return GetSingleton();
}

void Scene::FixedUpdatePlainComponents()
{
	for (size_t i = 0; i < mSpawnedEntityList.size(); i++)
	{
		if(IsValid(mSpawnedEntityList[i]) == true)
		{
			mSpawnedEntityList[i]->FixedUpdate_PlainComponent();
		}
	}
}

void Scene::UpdatePlainComponents()
{
	for (size_t i = 0; i < mSpawnedEntityList.size(); i++)
	{
		if (IsValid(mSpawnedEntityList[i]) == true)
		{
			mSpawnedEntityList[i]->Update_PlainComponent();
		}
	}
}

bool Scene::DestroyEntity_Internal(dooms::Entity* const entity) const
{
	bool isSuccess = false;

	D_ASSERT(IsValid(entity) == true);
	if(IsValid(entity) == true)
	{
		entity->SetIsPendingKill();
		isSuccess = true;
	}

	return isSuccess;
}

void Scene::InitializeEntity(dooms::Entity* const entity)
{
	entity->mInvolvedScene = this;
	entity->ChangeDObjectName(std::string{ "Entity " } + std::to_string(mSpawnedEntityList.size()));
	entity->SetOwnerDObject(this);
}

void Scene::RemoveEntityFromSpawnedEntityLIst(dooms::Entity* const entity)
{
	swap_popback::vector_find_swap_popback(mSpawnedEntityList, entity);
}

void dooms::Scene::OnEndOfFrameOfEntities()
{
	for (size_t i = 0; i < mSpawnedEntityList.size(); i++)
	{
		mSpawnedEntityList[i]->OnEndOfFramePlainComponentsAndEntity();
	}
}


NO_DISCARD dooms::Camera* Scene::GetMainCamera() const
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

const std::vector<Entity*>& Scene::GetEntitiesInScene() const
{
	return mSpawnedEntityList;
}
