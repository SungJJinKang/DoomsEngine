#include "Entity.h"

#include <algorithm>

#include"Scene.h"
#include "Layer/LayerManager.h"

using namespace dooms;

Entity::Entity(size_t entityID, Entity* parent) : 
	mEntityID{ entityID }, 
	mComponents{},
	mParentEntity{ parent }, 
	mChilds{}, 
	mTransform{}
{
	AddToRootObjectList();
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

void Entity::OnEntityMobilityChanged() const
{
	for(Component* component : mComponents)
	{
		if(IsValid(component))
		{
			component->OnEntityMobilityChanged(mEntityMobility);
		}
	}
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

bool Entity::_RemoveComponent(Component* const component, const size_t index)
{
	D_ASSERT(IsValid(component));
	D_ASSERT(component->IsChildOf<Transform>() == false);
	D_ASSERT(component->mOwnerEntity == this);
			
	bool isRemoveSuccess = false;
			
	D_ASSERT(mComponents.size() > 0);
	D_ASSERT(mComponents[index]);
	D_ASSERT(mComponents[index] == component);
			
	mComponents.erase(mComponents.begin() + index);
	isRemoveSuccess = true;
	component->SetIsPendingKill();

	return isRemoveSuccess;
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

	IsEnabled = false;
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
	D_ASSERT(layerIndex < LayerManager::GetSingleton()->GetLayerCount());
	mLayerIndex = layerIndex;
}


void Entity::SetEntityMobility(eEntityMobility entityMobility)
{
	mEntityMobility = entityMobility;

	OnEntityMobilityChanged();
}

void Entity::OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField)
{
	DObject::OnChangedByGUI(dFieldOfChangedField);

	if(dFieldOfChangedField.CompareWithFieldName("mEntityMobility"))
	{
		SetEntityMobility(mEntityMobility);
	}
}

bool Entity::RemoveComponent(Component* const component)
{
	D_ASSERT(IsValid(component));
	D_ASSERT(component->IsChildOf<Transform>() == false);
	D_ASSERT(component->mOwnerEntity == this);

	bool isSuccess = false;

	if (component->IsChildOf<Transform>() == false)
	{
		size_t index = 0;

		for (size_t i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] == component)
			{
				index = i;
				isSuccess = true;
				break;
			}
		}

		if (isSuccess == true)
		{
			isSuccess = _RemoveComponent(component, index);
		}
	}

	return isSuccess;
}

const std::vector<Component*>& Entity::GetAllComponents() const
{
	return mComponents;
}

void Entity::Destroy()
{
	//Work Flow : Scene::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	Scene::GetCurrentWorld()->DestroyEntity(*this);

}

