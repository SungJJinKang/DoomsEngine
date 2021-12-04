#include "Entity.h"

#include <algorithm>

#include"Scene.h"
#include <Scene/Layer.h>

using namespace dooms;

Entity::Entity(size_t entityID, Entity* parent) : 
	mEntityID{ entityID }, 
	mComponents{},
	mParentEntity{ parent }, 
	mChilds{}, 
	mTransform{}
{
	InitializeComponent(&mTransform);
}

Entity::~Entity()
{
	
}


void dooms::Entity::InitEntity()
{
}

void Entity::FixedUpdateEntity()
{
	FixedUpdateComponents();
}

void dooms::Entity::UpdateEntity()
{
	UpdateComponents();
}

void dooms::Entity::EndOfFrameEntity()
{
	EndOfFrameComponents();
	FrameDirtyChecker_EndOfFrame();
}

void Entity::SetInvoledScene(Scene* const scene)
{
	mInvolvedScene = scene;
}


void Entity::FixedUpdateComponents()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if(mComponents[i]->IsComponentEnabled == true)
		{
			mComponents[i]->FixedUpdateComponent_Internal();
			mComponents[i]->FixedUpdateComponent();
		}
	}
}

void dooms::Entity::UpdateComponents()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i]->IsComponentEnabled == true)
		{
			//D_START_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i), eProfileLayers::CPU);
			mComponents[i]->UpdateComponent_Internal();
			mComponents[i]->UpdateComponent();
			//D_END_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i));
		}
	}
}

void dooms::Entity::EndOfFrameComponents()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i]->IsComponentEnabled == true)
		{
			mComponents[i]->OnEndOfFrame_Component_Internal();
			mComponents[i]->OnEndOfFrame_Component();
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

	for (Component* const component : fromCopyedEnitty.mComponents)
	{
		Component* clonedNeComponent = static_cast<Component*>(component->CloneObject());

		D_ASSERT(IsValid(clonedNeComponent));

		toCopyedEntity._AddComponentAndInitialize(clonedNeComponent);
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
	while (mComponents.empty() == false)
	{
		//Why doesn't erase from vector instantly : for performance
		_RemoveComponent(mComponents[mComponents.size() - 1], mComponents.size() - 1);
	}
	mComponents.clear();
}

void Entity::OnDestroyed()
{
	ClearComponents();

	D_ASSERT(IsValid(mInvolvedScene) == true);
	mInvolvedScene->RemoveEntityFromSpawnedEntityLIst(this);
}

void Entity::OnSetPendingKill()
{
	Base::OnSetPendingKill();
	
	OnDestroyed();
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

