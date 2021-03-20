#include "BVH_Node_Container.h"

#include "BVH.h"
template <typename ColliderType>
void doom::BVH_Node_Container<ColliderType>::InsertBVHLeafNode(BVH<ColliderType>& BVH, const ColliderType& Collider, doom::physics::Collider* collider)
{
	//D_ASSERT(this->mBVH_NODE.IsValid() == true);
	this->mBVH_NODE = BVH.InsertLeaf(Collider, collider);
}

template <typename ColliderType>
void doom::BVH_Node_Container<ColliderType>::UpdateBVH_Node(const ColliderType& Collider)
{
	D_ASSERT(this->mBVH_NODE.IsValid() == true);
	this->mBVH_NODE = this->mBVH_NODE->Update(Collider);
}

/*
template <typename ColliderType>
void doom::BVH_Node_Container<ColliderType>::UpdateBVH_Node(const typename ColliderType::component_type& movedVector)
{
	D_ASSERT(this->mBVH_NODE != nullptr);
	this->mBVH_NODE = this->mBVH_NODE->Update(movedVector);
}
*/

template <typename ColliderType>
void doom::BVH_Node_Container<ColliderType>::RemoveBVH_Node()
{
	if (this->mBVH_NODE.IsValid())
	{
		this->mBVH_NODE->RemoveNode();
		this->mBVH_NODE.Reset();
	}
}

template <typename ColliderType>
doom::BVH_Node_Container<ColliderType>::~BVH_Node_Container()
{
	this->RemoveBVH_Node();
}


template <typename ColliderType>
bool doom::BVH_Node_Container<ColliderType>::RaycastToBVHNode(const physics::Ray& ray)
{
	D_ASSERT(this->mBVH_NODE.IsValid() == true);
	return this->mBVH_NODE->GetOwnerBVH()->BVHRayCast(ray);
}

template class doom::BVH_Node_Container<doom::physics::AABB2D>;
template class doom::BVH_Node_Container<doom::physics::AABB3D>;
template class doom::BVH_Node_Container<doom::physics::Sphere>;

