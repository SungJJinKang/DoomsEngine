#include "BVH_AABB_Container.h"

template <typename AABB>
void doom::BVH_AABB_Container<AABB>::ApplyModelMatrixToWorld_BVH_AABB()
{
	doom::physics::ApplyModelMatrixToAABB3D(this->GetLocalAABB3D(), this->GetModelMatrix(), this->GetWorldAABB3D());
}

template <typename AABB>
void doom::BVH_AABB_Container<AABB>::UpdateLocalAABB3D(const physics::AABB3D& aabb3d)
{
	this->mLocalAABB3D = aabb3d;
	this->IsWorldBVHAABBDirty = true;
}

template <typename AABB>
doom::physics::AABB3D doom::BVH_AABB_Container<AABB>::GetLocalAABB3D()
{
	return this->mLocalAABB3D;
}

template <typename AABB>
const doom::physics::AABB3D& doom::BVH_AABB_Container<AABB>::GetLocalAABB3D() const
{
	return this->mLocalAABB3D;
}

template <typename AABB>
doom::physics::AABB3D doom::BVH_AABB_Container<AABB>::GetWorldAABB3D()
{
	D_ASSERT(this->IsWorldBVHAABBDirty.HasDirtySender() == true);

	if (this->IsWorldBVHAABBDirty.GetIsDirty(true))
	{
		this->ApplyModelMatrixToWorld_BVH_AABB();
	}
	return this->mWorldAABB3D;
}

template <typename AABB>
const doom::physics::AABB3D& doom::BVH_AABB_Container<AABB>::GetWorldAABB3D() const
{
	D_ASSERT(this->IsWorldBVHAABBDirty.HasDirtySender() == true);

	if (this->IsWorldBVHAABBDirty.GetIsDirty(true))
	{
		this->ApplyModelMatrixToWorld_BVH_AABB();
	}
	return this->mWorldAABB3D;
}



template class doom::BVH_AABB_Container<doom::physics::AABB2D>;
template class doom::BVH_AABB_Container<doom::physics::AABB3D>;