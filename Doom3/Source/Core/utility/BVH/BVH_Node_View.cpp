#include "BVH_Node_View.h"

#include "BVH_Node.h"

template <typename ColliderType>
typename doom::BVH_Node_View<ColliderType>::node_type* doom::BVH_Node_View<ColliderType>::operator->()
{
	D_ASSERT(this->IsValid() == true);
	return (*mNodeArrayPointer) + this->mNodeIndex;
}

template class doom::BVH_Node_View<doom::physics::AABB2D>;
template class doom::BVH_Node_View<doom::physics::AABB3D>;
template class doom::BVH_Node_View<doom::physics::Sphere>;