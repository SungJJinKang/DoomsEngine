#include "ColliderComponent.h"

#include "Physics_Server.h"

#include <Entity.h>
#include <Rendering/Renderer/Renderer.h>


void doom::ColliderComponent::ResetAllCollisionState()
{
	this->mbIsColliderEnter = false;
	this->mbIsColliderExit = false;
	this->mbIsColliderStay = false;

	this->mbIsTriggerEnter = false;
	this->mbIsTriggerExit = false;
	this->mbIsTriggerStay = false;
}

void doom::ColliderComponent::InitComponent()
{
	this->AddLocalDirtyToTransformDirtyReceiver(this->bmIsWorldColliderDirty);
	this->AddLocalDirtyToTransformDirtyReceiver(this->IsWorldColliderCacheDirty);

	this->AutoColliderSetting();

	this->InsertBVHLeafNode(physics::Physics_Server::GetSingleton()->mPhysicsColliderBVH, *(this->GetWorldColliderCacheByReference()), this->GetWorldCollider());
}

void doom::ColliderComponent::UpdateComponent()
{
	this->UpdatePhysics();
}

void doom::ColliderComponent::FixedUpdateComponent()
{
}

void doom::ColliderComponent::OnEndOfFrame_Component()
{

}

void doom::ColliderComponent::OnDestroy()
{
	this->ResetAllCollisionState();
}

void doom::ColliderComponent::OnActivated()
{
	this->ResetAllCollisionState();
}

void doom::ColliderComponent::OnDeActivated()
{
	this->ResetAllCollisionState();
}

void doom::ColliderComponent::UpdateLocalBVhAABBCacheFromLocalCollider()
{
	D_ASSERT(this->bmIsLocalColliderDirty.GetIsDirty(false) == false); // LocalCollider must be already updated before update LocalBVhAABB

	this->UpdateLocalColliderCache(this->ExtractLocalAABB3D());
}

void doom::ColliderComponent::AutoColliderSetting()
{
	physics::AABB3D aabb3dFromMesh{};
	bool isHaveMeshAABB3D = this->GetMeshAABB3D(aabb3dFromMesh);
	if (isHaveMeshAABB3D == true)
	{
		this->AutoColliderSettingFromAABB3D(aabb3dFromMesh);

		math::Vector3 offset{ this->GetOffsetVector3() };

		aabb3dFromMesh.mLowerBound += offset; // add offset of LocalCollider
		aabb3dFromMesh.mUpperBound += offset;
		this->UpdateLocalColliderCache(aabb3dFromMesh); // LocalBVhAABBCache contain offset of LocalCollider
	}
}

bool doom::ColliderComponent::GetMeshAABB3D(physics::AABB3D& aabb3D)
{
	const Renderer* renderer = this->GetOwnerEntity()->GetComponent<Renderer>();
	if (renderer != nullptr)
	{
		aabb3D = renderer->GetLocalAABBBound();
		return true;
	}
	else
	{
		return false;
	}
}

const math::Matrix4x4& doom::ColliderComponent::GetModelMatrix() const
{
	return this->GetTransform()->GetModelMatrix();
}

void doom::ColliderComponent::UpdateLocalColliderAndLocalBVhAABBCache()
{
	if (this->bmIsLocalColliderDirty.GetIsDirty(true))
	{
		this->UpdateLocalCollider();
		this->bmIsWorldColliderDirty.SetDirty(true);

		this->UpdateLocalBVhAABBCacheFromLocalCollider(); // when transform data is changed, Updating LocalBvhAABBCache is not required. ( ModelMatrix will do that ) 
	}
}

void doom::ColliderComponent::OnPreUpdatePhysics()
{
	UpdateLocalColliderAndLocalBVhAABBCache();

	if (this->bmIsWorldColliderDirty.GetIsDirty(true))
	{
		// Maybe this is required only when pass BVH TEST with BVH_AABB
		// I know, but i think UpdatingWorldCollider is not expensive, So just do this
		// 
		// WorldBVhAABBCache will be updated when Raycast or CollisionCheck

		this->UpdateWorldCollider(); 
		
	}
}

void doom::ColliderComponent::UpdatePhysics()
{
}

void doom::ColliderComponent::OnPostUpdatePhysics()
{
}

void doom::ColliderComponent::SetIsLocalColliderDirty()
{
	this->bmIsLocalColliderDirty.SetDirty(true);
}

