#include "ColliderUpdater.h"

template <typename ColliderType>
void doom::ColliderUpdater<ColliderType>::UpdateWorldColliderCache(bool force)
{
	if (this->IsWorldColliderCacheDirty.GetIsDirty(true) || force)
	{
		//	TO DO : When Rotate Object, ColliderType can be larged. 
		//			then whenever rotate object, BVH_Node can be reinserted everytime. this is expensive.
		ColliderType::ApplyModelMatrix(this->mLocalColliderCache, this->GetModelMatrix(), this->mWorldColliderCache);
	}
}


template <typename ColliderType>
void doom::ColliderUpdater<ColliderType>::UpdateLocalColliderCache(const ColliderType& aabb3d)
{
	this->mLocalColliderCache = aabb3d;
	this->IsWorldColliderCacheDirty = true;
}


template <typename ColliderType>
ColliderType doom::ColliderUpdater<ColliderType>::GetLocalColliderCache()
{
	return this->mLocalColliderCache;
}

template <typename ColliderType>
const ColliderType* doom::ColliderUpdater<ColliderType>::GetLocalColliderCache() const
{
	return &(this->mLocalColliderCache);
}

template <typename ColliderType>
const ColliderType* doom::ColliderUpdater<ColliderType>::GetWorldColliderCacheByReference()
{
	D_ASSERT(this->IsWorldColliderCacheDirty.HasDirtySender() == true); // must register IsWorldBVhColliderCacheDirty to Object's Transform DirtySencer

	this->UpdateWorldColliderCache(false);
	return &(this->mWorldColliderCache);
}

template<typename ColliderType>
void doom::ColliderUpdater<ColliderType>::DrawWorldColliderCache(eColor color, bool drawInstantly)
{
	this->mWorldColliderCache.DrawPhysicsDebugColor(color, drawInstantly);
}



template class doom::ColliderUpdater<doom::physics::AABB2D>;
template class doom::ColliderUpdater<doom::physics::AABB3D>;
template class doom::ColliderUpdater<doom::physics::Sphere>;