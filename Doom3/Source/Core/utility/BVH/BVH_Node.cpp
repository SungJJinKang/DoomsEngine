#include "BVH_Node.h"

#include "BVH.h"

template<typename ColliderType>
void doom::BVH_Node<ColliderType>::Clear()
{
	this->mOwnerBVH = nullptr;
	this->mCollider = nullptr;
	this->mIndex = NULL_NODE_INDEX;
	this->mParentIndex = NULL_NODE_INDEX;
	this->mLeftNode = NULL_NODE_INDEX;
	this->mRightNode = NULL_NODE_INDEX;
	this->mIsLeaf = false;
	this->bmIsActive = false;
}

template<typename ColliderType>
void doom::BVH_Node<ColliderType>::ValidCheck()
{
#ifdef DEBUG_MODE
	if (this->bmIsActive == true)
	{
		D_ASSERT(this->mOwnerBVH != nullptr);
		D_ASSERT(this->mIndex != NULL_NODE_INDEX);
		D_ASSERT(&(this->mOwnerBVH->mTree.mNodes[this->mIndex]) == this);

	}
	D_ASSERT(this->bmIsActive == true);
#endif
}

template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::UpdateNode()
{
	D_ASSERT(this->mIsLeaf == true); // Only Leaf Nodes can be updated by UpdateLeafNode Function
	D_ASSERT(&(this->mOwnerBVH->mTree.mNodes[this->mIndex]) == this);

	return this->mOwnerBVH->UpdateLeafNode(this->mIndex);
}

template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::Update(const ColliderType& collider)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mBoundingCollider = collider;
	return this->UpdateNode();
}

/// <summary>
/// this function don't chagne mEnlargedBoundingCollider if updated mBoundingCollider is still completly enclosed by mEnlargedBoundingCollider
/// </summary>
/// <param name="movedVector"></param>
template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::Update(const typename ColliderType::component_type& movedVector)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mBoundingCollider.SignedExpand(movedVector);
	return this->UpdateNode();
}

template <typename ColliderType>
typename doom::BVH_Node<ColliderType>::node_view_type doom::BVH_Node<ColliderType>::Update(const typename ColliderType::component_type& movedVector, const typename ColliderType::component_type& margin)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mBoundingCollider.Expand(margin);
	this->mBoundingCollider.SignedExpand(movedVector);
	return this->UpdateNode();
}

template <typename ColliderType>
void doom::BVH_Node<ColliderType>::RemoveNode()
{
	this->mOwnerBVH->RemoveLeafNode(this);
}

template <typename ColliderType>
doom::BVH<ColliderType>* doom::BVH_Node<ColliderType>::GetOwnerBVH()
{
	return this->mOwnerBVH;
}

template class doom::BVH_Node<doom::physics::AABB2D>;
template class doom::BVH_Node<doom::physics::AABB3D>;
template class doom::BVH_Node<doom::physics::Sphere>;