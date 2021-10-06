#include "Entity.h"

#include <algorithm>

#include"Scene.h"
#include <SequenceStringGenerator/SequenceStringGenerator.h>

using namespace doom;

Entity::Entity(size_t entityID, Entity* parent) : 
	mEntityID{ entityID }, 
	mEntityName{}, 
	mPlainComponents{}, 
	mParent{ parent }, 
	mChilds{}, 
	mComponentPtrCache{ nullptr },
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
	for (size_t i = 0; i < mPlainComponents.size(); i++)
	{
		mPlainComponents[i]->FixedUpdateComponent_Internal();
		mPlainComponents[i]->FixedUpdateComponent();
	}
}

void doom::Entity::Update_PlainComponent()
{
	for (size_t i = 0; i < mPlainComponents.size(); i++)
	{
		//D_START_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i), eProfileLayers::CPU);
		mPlainComponents[i]->UpdateComponent_Internal();
		mPlainComponents[i]->UpdateComponent();
		//D_END_PROFILING(SequenceStringGenerator::GetLiteralString("Update PlainComponents ", i));
	}
}

void doom::Entity::EndOfFrame_PlainComponent()
{
	for (size_t i = 0; i < mPlainComponents.size(); i++)
	{
		mPlainComponents[i]->OnEndOfFrame_Component_Internal();
		mPlainComponents[i]->OnEndOfFrame_Component();
	}
}

void Entity::SetEntityName(const std::string& entityName)
{
	mEntityName = entityName;
	DObject::ChangeDObjectName(entityName);
}

void Entity::ClearComponents()
{
	for (auto& plainComponent : mPlainComponents)
	{
		//Why doesn't erase from vector instantly : for performance
		_DestroyComponent(plainComponent);
	}
	mPlainComponents.clear();

	for (auto& ServerComponent : mServerComponents)
	{
		//Why doesn't erase from vector instantly : for performance
		_DestroyComponent(ServerComponent);
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


void Entity::AddLayerChangedCallback(void(*callback_ptr)(Entity&))
{
#ifdef DEBUG_MODE
	//check is callback is already contained
	auto iter = std::find(mLayerIndexChangedCallback.begin(), mLayerIndexChangedCallback.end(), callback_ptr);
	D_ASSERT(iter == mLayerIndexChangedCallback.end());
#endif

	mLayerIndexChangedCallback.push_back(callback_ptr);
}

void Entity::RemoveLayerChangedCallback(void(*callback_ptr)(Entity&))
{
	auto iter = std::find(mLayerIndexChangedCallback.begin(), mLayerIndexChangedCallback.end(), callback_ptr);
	D_ASSERT(iter != mLayerIndexChangedCallback.end());

	mLayerIndexChangedCallback.erase(iter);
}

void Entity::SetLayerIndex(unsigned int layerIndex)
{
	D_ASSERT(layerIndex >= 0 && layerIndex < MAX_LAYER_COUNT);
	mLayerIndex = layerIndex;

	for (auto& callback : mLayerIndexChangedCallback)
	{
		callback(*this);
	}
}

void Entity::Destroy()
{
	//Work Flow : Scene::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	Scene::GetCurrentWorld()->DestroyEntity(*this);
	
}

