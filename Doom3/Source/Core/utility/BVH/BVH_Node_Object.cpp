#include "BVH_Node_Object.h"

template <typename ColliderType>
void doom::BVH_Node_Object<ColliderType>::UpdateBVH_Node()
{
	if (doom::ColliderUpdater<ColliderType>::IsWorldColliderCacheDirty.GetIsDirty(false) == true)
	{//Only when WorldAABB is updated,
		doom::BVH_Node_Container<ColliderType>::UpdateBVH_Node(*(doom::ColliderUpdater<ColliderType>::GetWorldCollider()));
	}
	
}

template <typename ColliderType>
doom::BVH_Node_Object<ColliderType>::~BVH_Node_Object()
{
}

//template class doom::BVH_Node_Object<doom::physics::AABB2D>;
template class doom::BVH_Node_Object<doom::physics::AABB3D>;
template class doom::BVH_Node_Object<doom::physics::Sphere>;