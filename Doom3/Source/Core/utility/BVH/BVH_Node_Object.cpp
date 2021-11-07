#include "BVH_Node_Object.h"

template <typename ColliderType>
void dooms::BVH_Node_Object<ColliderType>::UpdateBVH_Node()
{
	if (dooms::ColliderUpdater<ColliderType>::IsWorldColliderCacheDirty.GetIsDirty(false) == true)
	{//Only when WorldAABB is updated,
		dooms::BVH_Node_Container<ColliderType>::UpdateBVH_Node(*(dooms::ColliderUpdater<ColliderType>::GetWorldCollider()));
	}
	
}

template <typename ColliderType>
dooms::BVH_Node_Object<ColliderType>::~BVH_Node_Object()
{
}

//template class dooms::BVH_Node_Object<dooms::physics::AABB2D>;
template class dooms::BVH_Node_Object<dooms::physics::AABB3D>;
template class dooms::BVH_Node_Object<dooms::physics::Sphere>;