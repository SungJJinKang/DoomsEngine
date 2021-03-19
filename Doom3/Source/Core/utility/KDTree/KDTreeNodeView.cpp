#include "KDTreeNodeView.h"

#include "KDTreeNode.h"

template<int Dimension>
typename doom::KDTreeNodeView<Dimension>::node_type* doom::KDTreeNodeView<Dimension>::operator->()
{
	D_ASSERT(this->IsValid() == true);
	return (*mNodeArrayPointer) + this->mNodeIndex;
}

template class doom::KDTreeNodeView<2>;
template class doom::KDTreeNodeView<3>;