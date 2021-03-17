#include "BVH_AABB_Container.h"

template <typename AABB>
void doom::BVH_AABB_Container<AABB>::UpdateWorldBVhAABBCache(bool force)
{
	if (this->IsWorldBVhAABBCacheDirty.GetIsDirty(true) || force)
	{
		//	TO DO : When Rotate Object, AABB can be larged. 
		//			then whenever rotate object, BVH_Node can be reinserted everytime. this is expensive.
		doom::physics::ApplyModelMatrixToAABB(this->mLocalBVhAABBCache, this->GetModelMatrix(), this->mWorldBVhAABBCache);
	}
}


template <typename AABB>
void doom::BVH_AABB_Container<AABB>::UpdateLocalBVhAABBCache(const AABB& aabb3d)
{
	this->mLocalBVhAABBCache = aabb3d;
	this->IsWorldBVhAABBCacheDirty = true;
}


template <typename AABB>
AABB doom::BVH_AABB_Container<AABB>::GetLocalBVhAABB3DCache()
{
	return this->mLocalBVhAABBCache;
}

template <typename AABB>
const AABB& doom::BVH_AABB_Container<AABB>::GetLocalBVhAABB3DCache() const
{
	return this->mLocalBVhAABBCache;
}

template <typename AABB>
const AABB& doom::BVH_AABB_Container<AABB>::GetWorldBVhAABB3DCacheByReference()
{
	D_ASSERT(this->IsWorldBVhAABBCacheDirty.HasDirtySender() == true); // must register IsWorldBVhAABBCacheDirty to Object's Transform DirtySencer

	this->UpdateWorldBVhAABBCache(false);
	return this->mWorldBVhAABBCache;
}

template<typename AABB>
void doom::BVH_AABB_Container<AABB>::DrawWorldBVhAABBCache(eColor color, bool drawInstantly)
{
	this->mWorldBVhAABBCache.DrawPhysicsDebugColor(color, drawInstantly);
}



template class doom::BVH_AABB_Container<doom::physics::AABB2D>;
template class doom::BVH_AABB_Container<doom::physics::AABB3D>;