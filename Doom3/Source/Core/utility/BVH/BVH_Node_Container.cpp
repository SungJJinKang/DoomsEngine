#include "BVH_Node_Container.h"

template <typename AABB>
void doom::BVH_Node_Container<AABB>::InsertBVHLeafNode(BVH<AABB>& BVH, const AABB& AABB, doom::physics::Collider* collider)
{
	D_ASSERT(this->mBVH_NODE == nullptr);
	this->mBVH_NODE = BVH.InsertLeaf(AABB, collider);
}

template <typename AABB>
void doom::BVH_Node_Container<AABB>::UpdateBVH_Node(const AABB& AABB)
{
	D_ASSERT(this->mBVH_NODE != nullptr);
	this->mBVH_NODE = this->mBVH_NODE->UpdateAABB(AABB);
}

template <typename AABB>
void doom::BVH_Node_Container<AABB>::RemoveBVH_Node()
{
	if (this->mBVH_NODE != nullptr)
	{
		this->mBVH_NODE->RemoveNode();
		this->mBVH_NODE = nullptr;
	}
}

template <typename AABB>
doom::BVH_Node_Container<AABB>::~BVH_Node_Container()
{
	this->RemoveBVH_Node();
}


template <typename AABB>
bool doom::BVH_Node_Container<AABB>::RaycastToBVHNode(const physics::Ray& ray)
{
	D_ASSERT(this->mBVH_NODE != nullptr);
	return this->mBVH_NODE->GetOwnerBVH()->BVHRayCast(ray);
}

template class doom::BVH_Node_Container<doom::physics::AABB2D>;
template class doom::BVH_Node_Container<doom::physics::AABB3D>;

