#include "BVH_Node.h"

#include "BVH.h"

template<typename ColliderType>
void doom::BVH_Node<ColliderType>::Clear()
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
void doom::BVH_Node<ColliderType>::ValidCheck() const
{
	D_ASSERT(GetIsValid() == true);
}

template<typename ColliderType>
bool doom::BVH_Node<ColliderType>::GetIsValid() const
{
	return bmIsActive == true && mOwnerBVH != nullptr && mIndex != NULL_NODE_INDEX && mOwnerBVH->GetNode(mIndex);
}

template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::UpdateNode()
{
	D_ASSERT(mIsLeaf == true); // Only Leaf Nodes can be updated by UpdateLeafNode Function
	D_ASSERT(mOwnerBVH->GetNode(mIndex) == this);

	return mOwnerBVH->UpdateLeafNode(mIndex);
}

template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::Update(const ColliderType& collider)
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
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::Update(const typename ColliderType::component_type& movedVector)
{
	D_ASSERT(mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	mBoundingCollider.SignedExpand(movedVector);
	return UpdateNode();
}

template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::Update(const typename ColliderType::component_type& movedVector, const typename ColliderType::component_type& margin)
{
	D_ASSERT(mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	mBoundingCollider.Expand(margin);
	mBoundingCollider.SignedExpand(movedVector);
	return UpdateNode();
}

template <typename ColliderType>
void doom::BVH_Node<ColliderType>::RemoveNode()
{
	mOwnerBVH->RemoveLeafNode(this);
}

template <typename ColliderType>
doom::BVH<ColliderType>* doom::BVH_Node<ColliderType>::GetOwnerBVH()
{
	return mOwnerBVH;
}

template <typename ColliderType>
const doom::BVH<ColliderType>* doom::BVH_Node<ColliderType>::GetOwnerBVH() const
{
	return mOwnerBVH;
}

template<typename ColliderType>
ColliderType& doom::BVH_Node<ColliderType>::GetBoundingCollider()
{
	return mBoundingCollider;
}

template<typename ColliderType>
const ColliderType& doom::BVH_Node<ColliderType>::GetBoundingCollider() const
{
	return mBoundingCollider;
}

template<typename ColliderType>
ColliderType& doom::BVH_Node<ColliderType>::GetEnlargedBoundingCollider()
{
	return mEnlargedBoundingCollider;
}

template<typename ColliderType>
const ColliderType& doom::BVH_Node<ColliderType>::GetEnlargedBoundingCollider() const
{
	return mEnlargedBoundingCollider;
}

template<typename ColliderType>
const doom::BVH_Node<ColliderType>* doom::BVH_Node<ColliderType>::GetParentNode() const
{
	doom::BVH_Node<ColliderType>* targetNode = nullptr;
	if (mOwnerBVH->GetIsNodeValid(mParentIndex) == true)
	{
		targetNode = mOwnerBVH->GetNode(mParentIndex);
	}
	return targetNode;
}

template<typename ColliderType>
const doom::BVH_Node<ColliderType>* doom::BVH_Node<ColliderType>::GetLeftChildNode() const
{
	doom::BVH_Node<ColliderType>* targetNode = nullptr;
	if (mOwnerBVH->GetIsNodeValid(mLeftNode) == true)
	{
		targetNode = mOwnerBVH->GetNode(mLeftNode);
	}
	return targetNode;
}

template<typename ColliderType>
const doom::BVH_Node<ColliderType>* doom::BVH_Node<ColliderType>::GetRightChildNode() const
{
	doom::BVH_Node<ColliderType>* targetNode = nullptr;
	if (mOwnerBVH->GetIsNodeValid(mRightNode) == true)
	{
		targetNode = mOwnerBVH->GetNode(mRightNode);
	}
	return targetNode;
}

template class doom::BVH_Node<doom::physics::AABB2D>;
template class doom::BVH_Node<doom::physics::AABB3D>;
template class doom::BVH_Node<doom::physics::Sphere>;