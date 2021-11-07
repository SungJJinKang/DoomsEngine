#include "KDTreeNodeView.h"

#include "KDTree.h"

template<typename T>
typename dooms::KDTreeNodeView<T>::node_type* dooms::KDTreeNodeView<T>::operator->()
{
	D_ASSERT(IsValid() == true);
	return mKDTreePointer->mKDTreeNodes + mNodeIndex;
}

//template class dooms::KDTreeNodeView<math::Vector2>;
//template class dooms::KDTreeNodeView<math::Vector3>;
//template class dooms::KDTreeNodeView<dooms::physics::AABB3D>;