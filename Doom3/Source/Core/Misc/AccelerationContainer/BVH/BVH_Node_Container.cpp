#include "BVH_Node_Container.h"

#include "BVH.h"
template <typename ColliderType>
void dooms::BVH_Node_Container<ColliderType>::InsertBVHLeafNode(BVH<ColliderType>& BVH, const ColliderType& Collider, dooms::physics::Collider* collider)
{
	//D_ASSERT(mBVH_Node_View.IsValid() == true);
	mBVH_Node_View = BVH.InsertLeaf(Collider, collider);
}

template <typename ColliderType>
void dooms::BVH_Node_Container<ColliderType>::UpdateBVH_Node(const ColliderType& Collider)
{
	D_ASSERT(mBVH_Node_View.IsValid() == true);
	mBVH_Node_View = mBVH_Node_View.GetNode()->Update(Collider);
}

/*
template <typename ColliderType>
void dooms::BVH_Node_Container<ColliderType>::UpdateBVH_Node(const typename ColliderType::component_type& movedVector)
{
	D_ASSERT(mBVH_Node_View != nullptr);
	mBVH_Node_View = mBVH_Node_View->Update(movedVector);
}
*/

template <typename ColliderType>
void dooms::BVH_Node_Container<ColliderType>::RemoveBVH_Node()
{
	if (mBVH_Node_View.IsValid())
	{
		mBVH_Node_View->RemoveNode();
		mBVH_Node_View.Reset();
	}
}

template <typename ColliderType>
dooms::BVH_Node_Container<ColliderType>::BVH_Node_Container()
	:mBVH_Node_View()
{
}

template <typename ColliderType>
dooms::BVH_Node_Container<ColliderType>::~BVH_Node_Container()
{
	RemoveBVH_Node();
}

template <typename ColliderType>
dooms::BVH_Node_Container<ColliderType>::BVH_Node_Container(const BVH_Node_Container&)
	:mBVH_Node_View()
{
}


//template class dooms::BVH_Node_Container<dooms::physics::AABB2D>;
template class dooms::BVH_Node_Container<dooms::physics::AABB3D>;
template class dooms::BVH_Node_Container<dooms::physics::Sphere>;

