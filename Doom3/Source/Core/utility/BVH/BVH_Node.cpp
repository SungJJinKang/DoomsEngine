#include "BVH_Node.h"

#include "BVH.h"

template<typename AABB>
void doom::BVH_Node<AABB>::Clear()
{
	this->mOwnerBVH = nullptr;
	this->mCollider = nullptr;
	this->mIndex = NULL_NODE_INDEX;
	this->mParentIndex = NULL_NODE_INDEX;
	this->mChild1 = NULL_NODE_INDEX;
	this->mChild2 = NULL_NODE_INDEX;
	this->mIsLeaf = false;
	this->bmIsActive = false;
}

template<typename AABB>
void doom::BVH_Node<AABB>::ValidCheck()
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

template <typename AABB>
doom::BVH_Node<AABB>* doom::BVH_Node<AABB>::UpdateNode()
{
	D_ASSERT(this->mIsLeaf == true); // Only Leaf Nodes can be updated by UpdateLeafNode Function
	return this->mOwnerBVH->UpdateLeafNode(this);
}

template <typename AABB>
doom::BVH_Node<AABB>* doom::BVH_Node<AABB>::UpdateAABB(const AABB& newAABB)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mAABB = newAABB;
	return this->UpdateNode();
}

/// <summary>
/// this function don't chagne mEnlargedAABB if updated mAABB is still completly enclosed by mEnlargedAABB
/// </summary>
/// <param name="movedVector"></param>
template <typename AABB>
doom::BVH_Node<AABB>* doom::BVH_Node<AABB>::UpdateAABB(const typename AABB::component_type& movedVector)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mAABB.SignedExpand(movedVector);
	return this->UpdateNode();
}

template <typename AABB>
doom::BVH_Node<AABB>* doom::BVH_Node<AABB>::UpdateAABB(const typename AABB::component_type& movedVector, const typename AABB::component_type& margin)
{
	D_ASSERT(this->mIsLeaf == true); // Don try aabb of internalnode arbitrary, InternalNode should be changed only by BVH algorithm
	this->mAABB.Expand(margin);
	this->mAABB.SignedExpand(movedVector);
	return this->UpdateNode();
}

template <typename AABB>
void doom::BVH_Node<AABB>::RemoveNode()
{
	this->mOwnerBVH->RemoveLeafNode(this);
}

template <typename AABB>
doom::BVH<AABB>* doom::BVH_Node<AABB>::GetOwnerBVH()
{
	return this->mOwnerBVH;
}

template class doom::BVH_Node<doom::physics::AABB2D>;
template class doom::BVH_Node<doom::physics::AABB3D>;