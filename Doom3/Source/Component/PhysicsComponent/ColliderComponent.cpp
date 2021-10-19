#include "ColliderComponent.h"

#include "Physics_Server.h"

#include <Entity.h>
#include <Rendering/Renderer/Renderer.h>
#include "Rigidbody/Rigidbody.h"

void doom::ColliderComponent::AddThisComponentToRigidbody()
{
	doom::Rigidbody* const attachedRigidbodyComponent = GetOwnerEntity()->GetComponent<Rigidbody>();
	if(IsValid(attachedRigidbodyComponent) == true)
	{
		attachedRigidbodyComponent->AddColliderComponent(this);
	}
}

void doom::ColliderComponent::RemoveThisComponentFromRigidbody()
{
	doom::Rigidbody* const attachedRigidbodyComponent = GetOwnerEntity()->GetComponent<Rigidbody>();
	if (IsValid(attachedRigidbodyComponent) == true)
	{
		attachedRigidbodyComponent->RemoveColliderComponent(this);
	}
}


void doom::ColliderComponent::InitComponent()
{
	ServerComponent::InitComponent();

	AddLocalDirtyToTransformDirtyReceiver(bmIsWorldColliderDirty);
	AddLocalDirtyToTransformDirtyReceiver(IsWorldColliderCacheDirty);

	AutoColliderSetting();

	InsertBVHLeafNode(physics::Physics_Server::GetSingleton()->mPhysicsColliderBVH, *BVH_AABB3D_Node_Object::GetWorldCollider(), GetWorldCollider());

	AddThisComponentToRigidbody();
}

void doom::ColliderComponent::UpdateComponent()
{
	UpdatePhysics();
}

void doom::ColliderComponent::FixedUpdateComponent()
{
}

void doom::ColliderComponent::OnEndOfFrame_Component()
{

}

void doom::ColliderComponent::OnDestroy()
{
	RemoveThisComponentFromRigidbody();

}

void doom::ColliderComponent::OnActivated()
{
}

void doom::ColliderComponent::OnDeActivated()
{
}

void doom::ColliderComponent::UpdateLocalBVhAABBCacheFromLocalCollider()
{
	D_ASSERT(bmIsLocalColliderDirty.GetIsDirty(false) == false); // LocalCollider must be already updated before update LocalBVhAABB

	UpdateLocalColliderCache(ExtractLocalAABB3D());
}

void doom::ColliderComponent::AutoColliderSetting()
{
	physics::AABB3D aabb3dFromMesh{};
	bool isHaveMeshAABB3D = GetMeshAABB3D(aabb3dFromMesh);
	if (isHaveMeshAABB3D == true)
	{
		AutoColliderSettingFromAABB3D(aabb3dFromMesh);

		math::Vector4 offset{ GetOffsetVector3() };

		aabb3dFromMesh.mLowerBound += offset; // add offset of LocalCollider
		aabb3dFromMesh.mUpperBound += offset;
		UpdateLocalColliderCache(aabb3dFromMesh); // LocalBVhAABBCache contain offset of LocalCollider
	}
}


bool doom::ColliderComponent::GetMeshAABB3D(physics::AABB3D& aabb3D)
{
	const Renderer* renderer = GetOwnerEntity()->GetComponent<Renderer>();
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

const math::Matrix4x4& doom::ColliderComponent::GetModelMatrix()
{
	return GetTransform()->GetModelMatrix();
}

doom::ColliderComponent::~ColliderComponent()
{
}

void doom::ColliderComponent::UpdateLocalColliderAndLocalBVhAABBCache()
{
	if (bmIsLocalColliderDirty.GetIsDirty(true))
	{
		UpdateLocalCollider();
		bmIsWorldColliderDirty.SetDirty(true);

		UpdateLocalBVhAABBCacheFromLocalCollider(); // when transform data is changed, Updating LocalBvhAABBCache is not required. ( ModelMatrix will do that ) 
	}
}

void doom::ColliderComponent::OnPreUpdatePhysics()
{
	UpdateLocalColliderAndLocalBVhAABBCache();

	if (bmIsWorldColliderDirty.GetIsDirty(true))
	{
		// Maybe this is required only when pass BVH TEST with BVH_AABB
		// I know, but i think UpdatingWorldCollider is not expensive, So just do this
		// 
		// WorldBVhAABBCache will be updated when Raycast or CollisionCheck

		UpdateWorldCollider(); 
		UpdateBVH_Node();
		
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
	bmIsLocalColliderDirty.SetDirty(true);
}

