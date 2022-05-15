#include "ColliderUpdater.h"

template <typename ColliderType>
void dooms::ColliderUpdater<ColliderType>::UpdateWorldColliderCache(bool clearDirty)
{
	if (IsWorldColliderCacheDirty.GetIsDirty(clearDirty))
	{
		//	TO DO : When Rotate Object, ColliderType can be larged. 
		//			then whenever rotate object, BVH_Node can be reinserted everytime. this is expensive.
		ColliderType::ApplyModelMatrix(mLocalColliderCache, GetModelMatrix(), mWorldColliderCache);
	}
}

template <typename ColliderType>
bool dooms::ColliderUpdater<ColliderType>::CheckIsWorldColliderCacheDirty() const
{
	return IsWorldColliderCacheDirty.GetIsDirty(false);
}


template <typename ColliderType>
void dooms::ColliderUpdater<ColliderType>::UpdateLocalColliderCache(const ColliderType& aabb3d)
{
	mLocalColliderCache = aabb3d;
	IsWorldColliderCacheDirty = true;
}


template <typename ColliderType>
dooms::ColliderUpdater<ColliderType>::~ColliderUpdater()
{
}

template <typename ColliderType>
ColliderType dooms::ColliderUpdater<ColliderType>::GetLocalColliderCache()
{
	return mLocalColliderCache;
}

template <typename ColliderType>
const ColliderType* dooms::ColliderUpdater<ColliderType>::GetLocalColliderCache() const
{
	return &(mLocalColliderCache);
}

template <typename ColliderType>
const ColliderType* dooms::ColliderUpdater<ColliderType>::GetWorldCollider()
{
	D_ASSERT(IsWorldColliderCacheDirty.HasDirtySender() == true); // must register IsWorldBVhColliderCacheDirty to Object's Transform DirtySencer

	UpdateWorldColliderCache(true);
	return &(mWorldColliderCache);
}

template <typename ColliderType>
const ColliderType* dooms::ColliderUpdater<ColliderType>::GetWorldColliderWithoutUpdate() const
{
	return &(mWorldColliderCache);
}

template<typename ColliderType>
void dooms::ColliderUpdater<ColliderType>::DrawWorldColliderCache(eColor color, bool drawInstantly)
{
	UpdateWorldColliderCache(true);
	mWorldColliderCache.DrawCollider(color, drawInstantly);
}


template class dooms::ColliderUpdater<dooms::physics::AABB2D>;
template class dooms::ColliderUpdater<dooms::physics::AABB3D>;
template class dooms::ColliderUpdater<dooms::physics::Sphere>;