#include "BVH_Node_Object.h"

template <typename AABB>
void doom::BVH_Node_Object<AABB>::UpdateBVH_Node()
{
	if (this->IsWorldBVhAABBCacheDirty.GetIsDirty(false) == true)
	{//Only when WorldAABB is updated,
		doom::BVH_Node_Container<AABB>::UpdateBVH_Node(this->GetWorldBVhAABB3DCacheByReference());
	}
	
}

template class doom::BVH_Node_Object<doom::physics::AABB2D>;
template class doom::BVH_Node_Object<doom::physics::AABB3D>;