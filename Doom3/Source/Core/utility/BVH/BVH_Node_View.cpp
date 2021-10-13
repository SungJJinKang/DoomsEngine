#include "BVH_Node_View.h"

#include "BVH.h"

template <typename ColliderType>
typename doom::BVH_Node_View<ColliderType>::node_type* doom::BVH_Node_View<ColliderType>::operator->()
{
	D_ASSERT(IsValid() == true);
	return mOwnerBVH->GetNode(mNodeIndex);
}

template <typename ColliderType>
const typename doom::BVH_Node_View<ColliderType>::node_type* doom::BVH_Node_View<ColliderType>::operator->() const
{
	D_ASSERT(IsValid() == true);
	return mOwnerBVH->GetNode(mNodeIndex);
}





template class doom::BVH_Node_View<doom::physics::AABB2D>;
template class doom::BVH_Node_View<doom::physics::AABB3D>;
template class doom::BVH_Node_View<doom::physics::Sphere>;