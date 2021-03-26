#include "KDTreeNodeView.h"

#include "KDTree.h"
#include "KDTreeNode.h"

template<typename T>
typename doom::KDTreeNodeView<T>::node_type* doom::KDTreeNodeView<T>::operator->()
{
	D_ASSERT(this->IsValid() == true);
	return this->mKDTreePointer->mKDTreeNodes + this->mNodeIndex;
}

extern template class doom::KDTreeNodeView<math::Vector2>;
extern template class doom::KDTreeNodeView<math::Vector3>;
extern template class doom::KDTreeNodeView<doom::physics::AABB3D>;