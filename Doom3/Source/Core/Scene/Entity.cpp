#include "Entity.h"

#include <algorithm>

#include"Scene.h"
#include <Scene/Layer.h>

using namespace dooms;

Entity::Entity(size_t entityID, Entity* parent) : 
	mEntityID{ entityID }, 
	mPlainComponents{}, 
	mParentEntity{ parent }, 
	mChilds{}, 
	mTransform{}
{
	InitializeComponent(&mTransform);
	SetDObjectFlag(eDObjectFlag::NotCollectedByGC);
}

Entity::~Entity()
{
	ClearComponents();

	D_ASSERT(IsStrongValid(mInvolvedScene) == true);
	mInvolvedScene->RemoveEntityFromSpawnedEntityLIst(this);
}


void dooms::Entity::InitEntity()
{
}

void dooms::Entity::UpdateEntity()
{
}

void dooms::Entity::OnEndOfFramePlainComponentsAndEntity()
{
	EndOfFrame_PlainComponent();
	FrameDirtyChecker_EndOfFrame();
}


void Entity::FixedUpdate_PlainComponent()
{
	for (size_t i = 0; i < mPlainComponents.size(); i++)
	{
		if(mPlainComponents[i]->IsComponentEnabled == true)
		{
			mPlainComponents[i]->FixedUpdateComponent_Internal();
			mPlainComponents[i]->FixedUpdateComponent();
		}
	}
}

void dooms::Entity::Update_PlainComponent()
{
	for (size_t i = 0; i < mPlainComponents.size(); i++)
	{
		if (mPlainComponents[i]->IsComponentEnabled == true)
		{
			//D_START_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i), eProfileLayers::CPU);
			mPlainComponents[i]->UpdateComponent_Internal();
			mPlainComponents[i]->UpdateComponent();
			//D_END_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i));
		}
	}
}

void dooms::Entity::EndOfFrame_PlainComponent()
{
	for (size_t i = 0; i < mPlainComponents.size(); i++)
	{
		if (mPlainComponents[i]->IsComponentEnabled == true)
		{
			mPlainComponents[i]->OnEndOfFrame_Component_Internal();
			mPlainComponents[i]->OnEndOfFrame_Component();
		}
	}
}

void Entity::CopyEntity(const Entity& fromCopyedEnitty, Entity& toCopyedEntity)
{
	toCopyedEntity.ChangeDObjectName(fromCopyedEnitty.GetDObjectName());
	toCopyedEntity.mLayerIndex = fromCopyedEnitty.mLayerIndex;
	toCopyedEntity.mEntityMobility = fromCopyedEnitty.mEntityMobility;
	toCopyedEntity.mEntityFlag = fromCopyedEnitty.mEntityFlag;
	toCopyedEntity.mInvolvedScene = fromCopyedEnitty.mInvolvedScene;
	toCopyedEntity.mParentEntity = fromCopyedEnitty.mParentEntity;
	
	toCopyedEntity.mTransform = fromCopyedEnitty.mTransform;
	toCopyedEntity.InitializeComponent(&toCopyedEntity.mTransform);

	for (const PlainComponent* plainComponent : fromCopyedEnitty.mPlainComponents)
	{
		PlainComponent* clonedNewPlainComp = static_cast<PlainComponent*>(plainComponent->CloneObject());

		D_ASSERT(IsStrongValid(clonedNewPlainComp));

		toCopyedEntity._AddComponentAndInitialize(clonedNewPlainComp);
	}

	for(const ServerComponent* serverComponent : fromCopyedEnitty.mServerComponents)
	{
		ServerComponent* clonedNewServerComp = static_cast<ServerComponent*>(serverComponent->CloneObject());

		D_ASSERT(IsStrongValid(serverComponent));

		toCopyedEntity._AddComponentAndInitialize(clonedNewServerComp);
	}

	toCopyedEntity.mChilds.reserve(fromCopyedEnitty.mChilds.size());
	for(Entity* const child : fromCopyedEnitty.mChilds)
	{
		D_ASSERT(child != nullptr);

		Entity* duplicatedEntity = Scene::GetSingleton()->DuplicateEntity(child);
		toCopyedEntity.mChilds.push_back(duplicatedEntity);
	}


	
}

void Entity::SetEntityName(const std::string& entityName)
{
	ChangeDObjectName(entityName);
	DObject::ChangeDObjectName(entityName);
}

void Entity::InitializeComponent(Component* const newComponent)
{
	newComponent->SetOwnerDObject(this);

	newComponent->InitComponent_Internal(this);
	newComponent->InitComponent();
	newComponent->LateInitComponent();

	newComponent->OnActivated_Internal();
	newComponent->OnActivated();
}

void Entity::ClearComponents()
{
	while (mPlainComponents.empty() == false)
	{
		//Why doesn't erase from vector instantly : for performance
		_RemoveComponent(mPlainComponents[mPlainComponents.size() - 1], mPlainComponents.size() - 1);
	}
	mPlainComponents.clear();

	while (mServerComponents.empty() == false)
	{
		//Why doesn't erase from vector instantly : for performance
		_RemoveComponent(mServerComponents[mServerComponents.size() - 1], mServerComponents.size() - 1);
	}
	mServerComponents.clear();
}

void Entity::OnActivated()
{
	SetDirtyTrueAtThisFrame();
}

void Entity::DestroyEntitySelf()
{
	DestroySelf();
}

const std::string& Entity::GetEntityName() const
{
	return GetDObjectName();
}


void Entity::SetLayerIndex(UINT32 layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	mLayerIndex = layerIndex;
}

void Entity::Destroy()
{
	//Work Flow : Scene::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	Scene::GetCurrentWorld()->DestroyEntity(*this);
	
}

