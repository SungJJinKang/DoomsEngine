#include "Rigidbody.h"

#include <algorithm>

#include "Entity.h"
#include "../ColliderComponent.h"

void doom::Rigidbody::AddColliderComponent(ColliderComponent* const colliderComponent)
{
	auto iter = std::find(mAttachedColliderComponents.begin(), mAttachedColliderComponents.end(), colliderComponent);

	if(iter == mAttachedColliderComponents.end())
	{
		mAttachedColliderComponents.push_back(colliderComponent);
	}
}

void doom::Rigidbody::RemoveColliderComponent(ColliderComponent* const colliderComponent)
{
	auto iter = std::find(mAttachedColliderComponents.begin(), mAttachedColliderComponents.end(), colliderComponent);

	if (iter != mAttachedColliderComponents.end())
	{
		mAttachedColliderComponents.erase(iter);
	}
}

const std::vector<doom::ColliderComponent*>& doom::Rigidbody::GetAttachedColliderComponents() const
{
	return mAttachedColliderComponents;
}

void doom::Rigidbody::ClearCollideCollidersAtFrame()
{
	mCollideCollidersAtFrame.clear();
}

void doom::Rigidbody::InitializeAttachedColliderComponents()
{
	const std::vector<ColliderComponent*> attachedColliderComponents = GetOwnerEntity()->GetComponents<ColliderComponent>();
	for(ColliderComponent* colliderComponent : attachedColliderComponents)
	{
		AddColliderComponent(colliderComponent);
	}
}

void doom::Rigidbody::CheckIsRigidbodyComponentAlreadyExist()
{
	const std::vector<Rigidbody*> attachedColliderComponents = GetOwnerEntity()->GetComponents<Rigidbody>();
	D_ASSERT(attachedColliderComponents.size() == 1);
}

void doom::Rigidbody::InitComponent()
{
	ServerComponent::InitComponent();

	InitializeAttachedColliderComponents();

	CheckIsRigidbodyComponentAlreadyExist();
}

void doom::Rigidbody::UpdateComponent()
{
	ServerComponent::UpdateComponent();
}

void doom::Rigidbody::OnDestroy()
{
	ServerComponent::OnDestroy();

	ClearCollideCollidersAtFrame();
}

void doom::Rigidbody::OnActivated()
{
	ServerComponent::OnActivated();

	ClearCollideCollidersAtFrame();
}

void doom::Rigidbody::OnDeActivated()
{
	ServerComponent::OnDeActivated();

	ClearCollideCollidersAtFrame();
}
