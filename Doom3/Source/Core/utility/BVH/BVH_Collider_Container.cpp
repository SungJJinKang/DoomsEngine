#include "BVH_Collider_Container.h"

template <typename ColliderType>
void doom::BVH_Collider_Container<ColliderType>::UpdateWorldBVhColliderCache(bool force)
{
	if (this->IsWorldBVhColliderCacheDirty.GetIsDirty(true) || force)
	{
		//	TO DO : When Rotate Object, ColliderType can be larged. 
		//			then whenever rotate object, BVH_Node can be reinserted everytime. this is expensive.
		ColliderType::ApplyModelMatrix(this->mLocalBVhColliderCache, this->GetModelMatrix(), this->mWorldBVhColliderCache);
	}
}


template <typename ColliderType>
void doom::BVH_Collider_Container<ColliderType>::UpdateLocalBVhColliderCache(const ColliderType& aabb3d)
{
	this->mLocalBVhColliderCache = aabb3d;
	this->IsWorldBVhColliderCacheDirty = true;
}


template <typename ColliderType>
ColliderType doom::BVH_Collider_Container<ColliderType>::GetLocalBVhColliderCache()
{
	return this->mLocalBVhColliderCache;
}

template <typename ColliderType>
const ColliderType& doom::BVH_Collider_Container<ColliderType>::GetLocalBVhColliderCache() const
{
	return this->mLocalBVhColliderCache;
}

template <typename ColliderType>
const ColliderType& doom::BVH_Collider_Container<ColliderType>::GetWorldBVhColliderCacheByReference()
{
	D_ASSERT(this->IsWorldBVhColliderCacheDirty.HasDirtySender() == true); // must register IsWorldBVhColliderCacheDirty to Object's Transform DirtySencer

	this->UpdateWorldBVhColliderCache(false);
	return this->mWorldBVhColliderCache;
}

template<typename ColliderType>
void doom::BVH_Collider_Container<ColliderType>::DrawWorldBVhColliderCache(eColor color, bool drawInstantly)
{
	this->mWorldBVhColliderCache.DrawPhysicsDebugColor(color, drawInstantly);
}



template class doom::BVH_Collider_Container<doom::physics::AABB2D>;
template class doom::BVH_Collider_Container<doom::physics::AABB3D>;
template class doom::BVH_Collider_Container<doom::physics::Sphere>;