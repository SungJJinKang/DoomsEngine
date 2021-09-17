#include "ColliderUpdater.h"

template <typename ColliderType>
void doom::ColliderUpdater<ColliderType>::UpdateWorldColliderCache(bool clearDirty)
{
	if (IsWorldColliderCacheDirty.GetIsDirty(clearDirty))
	{
		//	TO DO : When Rotate Object, ColliderType can be larged. 
		//			then whenever rotate object, BVH_Node can be reinserted everytime. this is expensive.
		ColliderType::ApplyModelMatrix(mLocalColliderCache, GetModelMatrix(), mWorldColliderCache);
	}
}


template <typename ColliderType>
void doom::ColliderUpdater<ColliderType>::UpdateLocalColliderCache(const ColliderType& aabb3d)
{
	mLocalColliderCache = aabb3d;
	IsWorldColliderCacheDirty = true;
}


template <typename ColliderType>
ColliderType doom::ColliderUpdater<ColliderType>::GetLocalColliderCache()
{
	return mLocalColliderCache;
}

template <typename ColliderType>
const ColliderType* doom::ColliderUpdater<ColliderType>::GetLocalColliderCache() const
{
	return &(mLocalColliderCache);
}

template <typename ColliderType>
const ColliderType* doom::ColliderUpdater<ColliderType>::GetWorldColliderCache()
{
	D_ASSERT(IsWorldColliderCacheDirty.HasDirtySender() == true); // must register IsWorldBVhColliderCacheDirty to Object's Transform DirtySencer

	UpdateWorldColliderCache(true);
	return &(mWorldColliderCache);
}

template<typename ColliderType>
void doom::ColliderUpdater<ColliderType>::DrawWorldColliderCache(eColor color, bool drawInstantly)
{
	UpdateWorldColliderCache(true);
	mWorldColliderCache.Render(color, drawInstantly);
}


template class doom::ColliderUpdater<doom::physics::AABB2D>;
template class doom::ColliderUpdater<doom::physics::AABB3D>;
template class doom::ColliderUpdater<doom::physics::Sphere>;