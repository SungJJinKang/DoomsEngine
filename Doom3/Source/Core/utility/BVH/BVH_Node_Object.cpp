#include "BVH_Node_Object.h"

template <typename AABB>
void doom::BVH_Node_Object<AABB>::UpdateBVH_Node()
{
	this->UpdateBVH_Node(this->GetWorldAABB3D());
}

template class doom::BVH_Node_Object<doom::physics::AABB2D>;
template class doom::BVH_Node_Object<doom::physics::AABB3D>;