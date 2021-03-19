#include "KDTree.h"

template<int Dimension>
int doom::KDTree<Dimension>::AllocateNode(const typename node_type::component_type& point)
{
	int newNodeIndex;
	if (this->mFreedNodeIndexList.empty() == false)
	{// if there is freedNode
		newNodeIndex = this->mFreedNodeIndexList.front();
		this->mFreedNodeIndexList.pop();
	}
	else
	{
		this->mCurrentAllocatedNodeCount++;

		D_ASSERT(this->mCurrentAllocatedNodeCount <= this->mNodeCapacity);

		newNodeIndex = this->mCurrentAllocatedNodeCount - 1;
	}

	this->mCurrentActiveNodeCount++;

	this->mKDTreeNodes[newNodeIndex].mPoint = point;
	this->mKDTreeNodes[newNodeIndex].mIndex = newNodeIndex;
	this->mKDTreeNodes[newNodeIndex].bmIsActive = true;

	return newNodeIndex;
}

template<int Dimension>
void doom::KDTree<Dimension>::FreeNode(int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);

	this->mKDTreeNodes[index].mIndex = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].mDimension = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].bmIsActive = false;
	this->mKDTreeNodes[index].mParentIndex = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].mChild1 = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].mChild2 = NULL_NODE_INDEX;

	this->mCurrentActiveNodeCount--;
	this->mFreedNodeIndexList.push(index);
}

template<int Dimension>
int doom::KDTree<Dimension>::_Insert(const typename node_type::component_type & point, int searchIndex, int parentIndex, const int searchDimension)
{
	if (searchIndex == NULL_NODE_INDEX)
	{
		searchIndex = this->AllocateNode(point);
		this->mKDTreeNodes[searchIndex].mDimension = searchDimension;
		this->mKDTreeNodes[searchIndex].mParentIndex = parentIndex;
	}
	else if (point == this->mKDTreeNodes[searchIndex].mPoint)
	{// when equal
		NEVER_HAPPEN;
	}
	else if (point[searchDimension] < this->mKDTreeNodes[searchIndex].mPoint[searchDimension])
	{
		this->mKDTreeNodes[searchIndex].mChild1 = _Insert(point, this->mKDTreeNodes[searchIndex].mChild1, searchIndex, (searchDimension + 1) % Dimension);
	}
	else
	{
		this->mKDTreeNodes[searchIndex].mChild2 = _Insert(point, this->mKDTreeNodes[searchIndex].mChild2, searchIndex, (searchDimension + 1) % Dimension);
	}
	
	return searchIndex;
}

template<int Dimension>
int doom::KDTree<Dimension>::_FineMin(const int index, const int searchDimension, const int targetMinNodeDimension)
{
	int minNode{ NULL_NODE_INDEX };
	
	if (index == NULL_NODE_INDEX)
	{
		return NULL_NODE_INDEX;
	}
	else if (searchDimension == targetMinNodeDimension)
	{
		minNode = index;
		if (this->mKDTreeNodes[index].mChild1 != NULL_NODE_INDEX)
		{
			minNode = this->_FineMin(this->mKDTreeNodes[index].mChild1, (searchDimension + 1) % Dimension, targetMinNodeDimension);	
		}
		return minNode;
	}
	else
	{
		minNode = NULL_NODE_INDEX;
		int minLeft = _FineMin(this->mKDTreeNodes[index].mChild1, (searchDimension + 1) % Dimension, targetMinNodeDimension);
		int minRigth = _FineMin(this->mKDTreeNodes[index].mChild2, (searchDimension + 1) % Dimension, targetMinNodeDimension);

		if (minLeft != NULL_NODE_INDEX && minRigth != NULL_NODE_INDEX)
		{
			if (this->mKDTreeNodes[minLeft].mPoint[searchDimension] < this->mKDTreeNodes[minRigth].mPoint[searchDimension])
			{
				minNode = minLeft;
			}
			else
			{
				minNode = minRigth;
			}
		}
		else
		{
			minNode = minLeft != NULL_NODE_INDEX ? minLeft : minRigth;
		}

		if (minNode != NULL_NODE_INDEX)
		{
			if (this->mKDTreeNodes[index].mPoint[searchDimension] < this->mKDTreeNodes[minNode].mPoint[searchDimension])
			{
				minNode = index;
			}
			return minNode;
		}
		else
		{
			return index;
		}
	}

	
}

template<int Dimension>
int doom::KDTree<Dimension>::_Delete(const typename node_type::component_type& point, int searchIndex, int parentIndex, const int searchDimension, const int targetMinNodeDimension)
{
	if (searchIndex == NULL_NODE_INDEX)
	{
		NEVER_HAPPEN;
	}
	else if (this->mKDTreeNodes[searchIndex].mPoint == point)
	{
		if (this->mKDTreeNodes[searchIndex].mChild2 != NULL_NODE_INDEX)
		{
			//Set searchIndex's Parent's mChild2 to RightSubtree's Most Left Node
			//Set searchIndex's Child2's Parent to RightSubtree's Most Left Node
			//Set searchIndex's Child1's Parent to RightSubtree's Most Left Node
			int deletedIndex = searchIndex;
			searchIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mChild2, (searchDimension + 1) % Dimension, targetMinNodeDimension);
			this->mKDTreeNodes[searchIndex].mChild2 = this->_Delete(point, this->mKDTreeNodes[searchIndex].mChild2, )
		}
		else if (this->mKDTreeNodes[searchIndex].mChild1 != NULL_NODE_INDEX)
		{

		}
	}
	elif point == node.point :
		if node.right :
			node.point = find_min(node.right, sDim, (sDim + 1) % tDims)
			node.right = delete(node.point, node.right, (sDim + 1) % tDims)
		elif node.left :
			node.point = find_min(node.left, sDim, (sDim + 1) % tDims)
			node.right = delete(node.point, node.left, (sDim + 1) % tDims)
			node.left = None
		else:
			node = None
	elif point[sDim] < node.point[sDim] :
		node.left = delete(point, node.left, (sDim + 1) % tDims)
	else:
		node.right = delete(point, node.right, (sDim + 1) % tDims)
	return node
}

template<int Dimension>
doom::KDTree<Dimension>::KDTree(int capacity)
	:mNodeCapacity{ capacity }
{
	this->mKDTreeNodes = new KDTreeNode<Dimension>[capacity]();
}

template<int Dimension>
typename doom::KDTree<Dimension>::node_view_type doom::KDTree<Dimension>::Insert(const typename node_type::component_type& point)
{
	int newNodexIndex = NULL_NODE_INDEX;
	if (this->mRootNodeIndex == NULL_NODE_INDEX)
	{
		newNodexIndex = this->AllocateNode(point);
		this->mRootNodeIndex = newNodexIndex;
		return this->MakeKDTree_Node_View(newNodexIndex);
	}
	newNodexIndex = this->_Insert(point, this->mRootNodeIndex, NULL_NODE_INDEX, 0);

	return this->MakeKDTree_Node_View(newNodexIndex);
}

template<int Dimension>
typename doom::KDTree<Dimension>::node_view_type doom::KDTree<Dimension>::Insert(const typename node_type::component_type& point, const int searchIndex, const int searchDimension)
{
	return node_view_type();
}

template<int Dimension>
void doom::KDTree<Dimension>::Delete(const typename node_type::component_type& point)
{
}

template<int Dimension>
void doom::KDTree<Dimension>::Delete(int nodeIndex)
{
}

template<int Dimension>
typename doom::KDTree<Dimension>::node_view_type doom::KDTree<Dimension>::FineMin(const int targetMinNodeDimension)
{
	D_ASSERT(targetMinNodeDimension >= 0 && targetMinNodeDimension < Dimension);
	int minNodeIndex = this->_FineMin(this->mRootNodeIndex, 0, targetMinNodeDimension);
	return this->MakeKDTree_Node_View(minNodeIndex);
}


template class doom::KDTree<2>;
template class doom::KDTree<3>;