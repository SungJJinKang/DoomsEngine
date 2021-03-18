#include "BVH_Tree.h"


template <typename ColliderType>
doom::BVH_Tree<ColliderType>::BVH_Tree(int nodeCapacity) : mNodeCapacity{ nodeCapacity }
{
	mNodes = new BVH_Node<ColliderType>[mNodeCapacity];
}

template <typename ColliderType>
doom::BVH_Tree<ColliderType>::~BVH_Tree()
{
	delete[] mNodes;
}

template class doom::BVH_Tree<doom::physics::AABB2D>;
template class doom::BVH_Tree<doom::physics::AABB3D>;
template class doom::BVH_Tree<doom::physics::Sphere>;