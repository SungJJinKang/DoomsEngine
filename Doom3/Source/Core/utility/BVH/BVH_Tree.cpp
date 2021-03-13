#include "BVH_Tree.h"


template <typename AABB>
doom::BVH_Tree<AABB>::BVH_Tree(int nodeCapacity) : mNodeCapacity{ nodeCapacity }
{
	mNodes = new BVH_Node<AABB>[mNodeCapacity];
}

template <typename AABB>
doom::BVH_Tree<AABB>::~BVH_Tree()
{
	delete[] mNodes;
}

template class doom::BVH_Tree<doom::physics::AABB2D>;
template class doom::BVH_Tree<doom::physics::AABB3D>;