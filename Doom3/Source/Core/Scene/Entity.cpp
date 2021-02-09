#include "Entity.h"

#include "../../Component/Transform.h"
#include"Scene.h"

using namespace doom;

Entity::Entity(Entity* parent) : mEntityName{}, mPlainComponents{}, mParent{ parent }, mChilds{}
{
	this->mTransform = this->AddComponent<Transform>();
}

Entity::~Entity()
{
	this->ClearComponents();
}


void doom::Entity::InitEntity()
{
}

void doom::Entity::UpdateEntity()
{
}

void doom::Entity::OnEndOfFrame()
{
	this->EndOfFrame_PlainComponent();

	this->FrameDirtyChecker_EndOfFrame();
}

void doom::Entity::Update_PlainComponent()
{
	for (auto& plainComponent : this->mPlainComponents)
	{
		plainComponent->UpdateComponent_Internal();
		plainComponent->UpdateComponent();
	}
}

void doom::Entity::EndOfFrame_PlainComponent()
{
	for (auto& plainComponent : this->mPlainComponents)
	{
		plainComponent->OnEndOfFrame_Component_Internal();
		plainComponent->OnEndOfFrame_Component();
	}
}




std::string_view Entity::GetEntityName() const
{
	return this->mEntityName;
}

Transform* Entity::GetTransform() const
{
	return this->mTransform;
}

void Entity::Destroy()
{
	//Work Flow : Scene::GetCurrentWorld().DestroyEntity -> delete Entity -> Entity::~Entity
	Scene::GetCurrentWorld()->DestroyEntity(*this);
	
}

