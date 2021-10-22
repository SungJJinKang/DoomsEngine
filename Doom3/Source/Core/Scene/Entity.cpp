#include "Entity.h"

#include <algorithm>

#include"Scene.h"
#include <Scene/Layer.h>

using namespace doom;

Entity::Entity(SIZE_T entityID, Entity* parent) : 
	mEntityID{ entityID }, 
	mEntityName{}, 
	mPlainComponents{}, 
	mParent{ parent }, 
	mChilds{}, 
	mTransform{}
{
	InitializeComponent(&mTransform);
}

Entity::~Entity()
{
	ClearComponents();
}


void doom::Entity::InitEntity()
{
}

void doom::Entity::UpdateEntity()
{
}

void doom::Entity::OnEndOfFramePlainComponentsAndEntity()
{
	EndOfFrame_PlainComponent();
	FrameDirtyChecker_EndOfFrame();
}


void Entity::FixedUpdate_PlainComponent()
{
	for (SIZE_T i = 0; i < mPlainComponents.size(); i++)
	{
		mPlainComponents[i]->FixedUpdateComponent_Internal();
		mPlainComponents[i]->FixedUpdateComponent();
	}
}

void doom::Entity::Update_PlainComponent()
{
	for (SIZE_T i = 0; i < mPlainComponents.size(); i++)
	{
		//D_START_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i), eProfileLayers::CPU);
		mPlainComponents[i]->UpdateComponent_Internal();
		mPlainComponents[i]->UpdateComponent();
		//D_END_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i));
	}
}

void doom::Entity::EndOfFrame_PlainComponent()
{
	for (SIZE_T i = 0; i < mPlainComponents.size(); i++)
	{
		mPlainComponents[i]->OnEndOfFrame_Component_Internal();
		mPlainComponents[i]->OnEndOfFrame_Component();
	}
}

void Entity::CopyEntity(const Entity& fromCopyedEnitty, Entity& toCopyedEntity)
{
	toCopyedEntity.mEntityName = fromCopyedEnitty.mEntityName;
	toCopyedEntity.mLayerIndex = fromCopyedEnitty.mLayerIndex;
	toCopyedEntity.mEntityMobility = fromCopyedEnitty.mEntityMobility;
	toCopyedEntity.mEntityFlag = fromCopyedEnitty.mEntityFlag;


	toCopyedEntity.mTransform = fromCopyedEnitty.mTransform;
	toCopyedEntity.InitializeComponent(&toCopyedEntity.mTransform);

	for (const std::unique_ptr<PlainComponent, Component::Deleter>& plainComponents : fromCopyedEnitty.mPlainComponents)
	{
		const PlainComponent* const plainComp = plainComponents.get();
		PlainComponent* clonedNewPlainComp = plainComp->CLONE_DOBJECT();

		D_ASSERT(clonedNewPlainComp != nullptr);

		toCopyedEntity._AddComponentAndInitialize(clonedNewPlainComp);
	}

	for(const std::unique_ptr<ServerComponent, Component::Deleter>& serverComponents : fromCopyedEnitty.mServerComponents)
	{
		const ServerComponent* const serverComp = serverComponents.get();
		ServerComponent* clonedNewServerComp = serverComp->CLONE_DOBJECT();

		D_ASSERT(serverComp != nullptr);

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
	mEntityName = entityName;
	DObject::ChangeDObjectName(entityName);
}

void Entity::InitializeComponent(Component* const newComponent)
{
	newComponent->SetOwnerDObject(this);

	newComponent->InitComponent_Internal(this);
	newComponent->InitComponent();

	newComponent->OnActivated_Internal();
	newComponent->OnActivated();
}

void Entity::ClearComponents()
{
	while (mPlainComponents.empty() == false)
	{
		//Why doesn't erase from vector instantly : for performance
		_RemoveComponent(mPlainComponents[mPlainComponents.size() - 1].get(), mPlainComponents.size() - 1);
	}
	mPlainComponents.clear();

	while (mServerComponents.empty() == false)
	{
		//Why doesn't erase from vector instantly : for performance
		_RemoveComponent(mServerComponents[mServerComponents.size() - 1].get(), mServerComponents.size() - 1);
	}
	mServerComponents.clear();
}

void Entity::OnActivated()
{
	SetDirtyTrueAtThisFrame();
}

std::string_view Entity::GetEntityName() const
{
	return mEntityName;
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

