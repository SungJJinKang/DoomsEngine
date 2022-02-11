#include "BVH_Node.h"

#include "BVH.h"

template<typename ColliderType>
void dooms::BVH_Node<ColliderType>::Clear()
{
	mOwnerBVH = nullptr;
	mCollider = nullptr;
	mIndex = NULL_NODE_INDEX;
	mParentIndex = NULL_NODE_INDEX;
	mLeftNode = NULL_NODE_INDEX;
	mRightNode = NULL_NODE_INDEX;
	mIsLeaf = false;
	bmIsActive = false;
}

template<typename ColliderType>
void dooms::BVH_Node<ColliderType>::ValidCheck() const
{
	D_ASSERT(GetIsValid() == true);
}

template <typename ColliderType>
typename dooms::BVH_Node<ColliderType>::node_view_type dooms::BVH_Node<ColliderType>::UpdateNode()
{
	D_ASSERT(mIsLeaf == true); // Only Leaf Nodes can be updated by UpdateLeafNode Function
	D_ASSERT(mOwnerBVH->GetNode(mIndex) == this);

	return mOwnerBVH->UpdateLeafNode(mIndex);
}

template <typename ColliderType>
typename dooms::BVH_Node<ColliderType>::node_view_type dooms::BVH_Node<ColliderType>::Update(const ColliderType& collider)
{
	D_ASSERT(mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	mBoundingCollider = collider;
	return UpdateNode();
}

/// <summary>
/// this function don't chagne mEnlargedBoundingCollider if updated mBoundingCollider is still completly enclosed by mEnlargedBoundingCollider
/// </summary>
/// <param name="movedVector"></param>
template <typename ColliderType>
typename dooms::BVH_Node<ColliderType>::node_view_type dooms::BVH_Node<ColliderType>::Update(const typename ColliderType::component_type& movedVector)
{
	D_ASSERT(mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	mBoundingCollider.SignedExpand(typename ColliderType::component_type(movedVector));
	return UpdateNode();
}

template <typename ColliderType>
typename dooms::BVH_Node<ColliderType>::node_view_type dooms::BVH_Node<ColliderType>::Update(const typename ColliderType::component_type& movedVector, const typename ColliderType::component_type& margin)
{
	D_ASSERT(mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	mBoundingCollider.Expand(typename ColliderType::component_type( margin ));
	mBoundingCollider.SignedExpand(typename ColliderType::component_type(movedVector));
	return UpdateNode();
}

template <typename ColliderType>
void dooms::BVH_Node<ColliderType>::RemoveNode()
{
	mOwnerBVH->RemoveLeafNode(this);
}

template<typename ColliderType>
const dooms::BVH_Node<ColliderType>* dooms::BVH_Node<ColliderType>::GetParentNode() const
{
	dooms::BVH_Node<ColliderType>* targetNode = nullptr;
	if (mOwnerBVH->GetIsNodeValid(mParentIndex) == true)
	{
		targetNode = mOwnerBVH->GetNode(mParentIndex);
	}
	return targetNode;
}


template struct dooms::BVH_Node<dooms::physics::AABB2D>;
template struct dooms::BVH_Node<dooms::physics::AABB3D>;
template struct dooms::BVH_Node<dooms::physics::Sphere>;