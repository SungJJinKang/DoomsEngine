#include "Rigidbody.h"

#include <algorithm>

#include <Scene/Entity.h>
#include "../ColliderComponent.h"

void dooms::Rigidbody::AddColliderComponent(ColliderComponent* const colliderComponent)
{
	auto iter = std::find(mAttachedColliderComponents.begin(), mAttachedColliderComponents.end(), colliderComponent);

	if(iter == mAttachedColliderComponents.end())
	{
		mAttachedColliderComponents.push_back(colliderComponent);
	}
}

void dooms::Rigidbody::RemoveColliderComponent(ColliderComponent* const colliderComponent)
{
	auto iter = std::find(mAttachedColliderComponents.begin(), mAttachedColliderComponents.end(), colliderComponent);

	if (iter != mAttachedColliderComponents.end())
	{
		mAttachedColliderComponents.erase(iter);
	}
}

const std::vector<dooms::ColliderComponent*>& dooms::Rigidbody::GetAttachedColliderComponents() const
{
	return mAttachedColliderComponents;
}

void dooms::Rigidbody::ClearCollideCollidersAtFrame()
{
	mCollideCollidersAtFrame.clear();
}

void dooms::Rigidbody::InitializeAttachedColliderComponents()
{
	const std::vector<ColliderComponent*> attachedColliderComponents = GetOwnerEntity()->GetComponents<ColliderComponent>();
	for(ColliderComponent* colliderComponent : attachedColliderComponents)
	{
		AddColliderComponent(colliderComponent);
	}
}

void dooms::Rigidbody::CheckIsRigidbodyComponentAlreadyExist()
{
	const std::vector<Rigidbody*> attachedColliderComponents = GetOwnerEntity()->GetComponents<Rigidbody>();
	D_ASSERT(attachedColliderComponents.size() == 1);
}

dooms::Rigidbody::Rigidbody()
{
}

dooms::Rigidbody::~Rigidbody()
{
}

dooms::Rigidbody::Rigidbody(const Rigidbody& rigid)
	:mAttachedColliderComponents(), mCollideCollidersAtFrame()
{
}

dooms::Rigidbody& dooms::Rigidbody::operator=(const Rigidbody& rigid)
{
	return *this;
}

void dooms::Rigidbody::InitComponent()
{
	Component::InitComponent();

	InitializeAttachedColliderComponents();

	CheckIsRigidbodyComponentAlreadyExist();
}

void dooms::Rigidbody::UpdateComponent()
{
	Component::UpdateComponent();
}

void dooms::Rigidbody::OnDestroy()
{
	Component::OnDestroy();

	ClearCollideCollidersAtFrame();
	StaticContainer<Rigidbody>::RemoveFromStaticContainer();
}

void dooms::Rigidbody::OnActivated()
{
	Component::OnActivated();

	ClearCollideCollidersAtFrame();
}

void dooms::Rigidbody::OnDeActivated()
{
	Component::OnDeActivated();

	ClearCollideCollidersAtFrame();
}
