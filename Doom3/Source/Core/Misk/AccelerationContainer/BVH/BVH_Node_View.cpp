#include "BVH_Node_View.h"

#include "BVH.h"

template <typename ColliderType>
typename dooms::BVH_Node_View<ColliderType>::node_type* dooms::BVH_Node_View<ColliderType>::operator->()
{
	D_ASSERT(IsValid() == true);
	return mOwnerBVH->GetNode(mNodeIndex);
}

template <typename ColliderType>
const typename dooms::BVH_Node_View<ColliderType>::node_type* dooms::BVH_Node_View<ColliderType>::operator->() const
{
	D_ASSERT(IsValid() == true);
	return mOwnerBVH->GetNode(mNodeIndex);
}





//stemplate class dooms::BVH_Node_View<dooms::physics::AABB2D>;
template class dooms::BVH_Node_View<dooms::physics::AABB3D>;
template class dooms::BVH_Node_View<dooms::physics::Sphere>;