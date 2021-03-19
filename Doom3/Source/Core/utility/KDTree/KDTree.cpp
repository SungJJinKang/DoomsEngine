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
	this->mKDTreeNodes[index].mLeftNode = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].mRightNode = NULL_NODE_INDEX;

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
		this->mKDTreeNodes[searchIndex].mLeftNode = _Insert(point, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, (searchDimension + 1) % Dimension);
	}
	else
	{
		this->mKDTreeNodes[searchIndex].mRightNode = _Insert(point, this->mKDTreeNodes[searchIndex].mRightNode, searchIndex, (searchDimension + 1) % Dimension);
	}
	
	return searchIndex;
}

template<int Dimension>
int doom::KDTree<Dimension>::_FineMin(const int index, const int searchDimension, const int targetMinNodeDimension)
{
	int minNode{ NULL_NODE_INDEX };
	
	int nextDimension = (searchDimension + 1) % Dimension;

	if (index == NULL_NODE_INDEX)
	{
		return NULL_NODE_INDEX;
	}
	else if (searchDimension == targetMinNodeDimension)
	{
		minNode = index;
		if (this->mKDTreeNodes[index].mLeftNode != NULL_NODE_INDEX)
		{
			minNode = this->_FineMin(this->mKDTreeNodes[index].mLeftNode, nextDimension, targetMinNodeDimension);
		}
		return minNode;
	}
	else
	{
		minNode = NULL_NODE_INDEX;
		int minLeft = _FineMin(this->mKDTreeNodes[index].mLeftNode, nextDimension, targetMinNodeDimension);
		int minRigth = _FineMin(this->mKDTreeNodes[index].mRightNode, nextDimension, targetMinNodeDimension);

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
	int nextDimension = (searchDimension + 1) % Dimension;
	if (searchIndex == NULL_NODE_INDEX)
	{
		NEVER_HAPPEN;
	}
	else if (this->mKDTreeNodes[searchIndex].mPoint == point)
	{
		int deletedIndex = searchIndex;

		if (this->mKDTreeNodes[searchIndex].mRightNode != NULL_NODE_INDEX)
		{
			//Set searchIndex's Parent's mRightNode to RightSubtree's Most Left Node
			//Set searchIndex's Child2's Parent to RightSubtree's Most Left Node
			//Set searchIndex's Child1's Parent to RightSubtree's Most Left Node
			searchIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mRightNode, nextDimension, targetMinNodeDimension);
			this->mKDTreeNodes[searchIndex].mRightNode = this->_Delete(point, this->mKDTreeNodes[searchIndex].mRightNode, searchIndex, nextDimension, targetMinNodeDimension);
		}
		else if (this->mKDTreeNodes[searchIndex].mLeftNode != NULL_NODE_INDEX)
		{
			int deletedIndex = searchIndex;
			searchIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mLeftNode, nextDimension, targetMinNodeDimension);
			this->mKDTreeNodes[searchIndex].mRightNode = this->_Delete(point, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextDimension, targetMinNodeDimension);
		}
		else
		{// searchIndex don't have child
			if (parentIndex != NULL_NODE_INDEX)
			{
				if (this->mKDTreeNodes[parentIndex].mLeftNode == searchIndex)
				{
					this->mKDTreeNodes[parentIndex].mLeftNode = NULL_NODE_INDEX;
				}
				else if (this->mKDTreeNodes[parentIndex].mRightNode == searchIndex)
				{
					this->mKDTreeNodes[parentIndex].mRightNode = NULL_NODE_INDEX;
				}
				else
				{
					NEVER_HAPPEN;
				}
			}
			this->FreeNode(deletedIndex);
		}


	}
	else if (point[searchDimension] < this->mKDTreeNodes[searchIndex].mPoint[searchDimension])
	{
		this->mKDTreeNodes[searchIndex].mLeftNode = this->_Delete(point, this->mKDTreeNodes[searchIndex].mLeftNode, nextDimension, targetMinNodeDimension);
	}
	else
	{
		this->mKDTreeNodes[searchIndex].mRightNode = this->_Delete(point, this->mKDTreeNodes[searchIndex].mRightNode, nextDimension, targetMinNodeDimension);
	}

	return searchIndex;
}

template <int Dimension>
void doom::KDTree<Dimension>::_SwapNode(int nodeIndex1, int nodeIndex2)
{
	int parentIndex1 = nodeIndex1 != NULL_NODE_INDEX ? this->mKDTreeNodes[nodeIndex1].mParentIndex : NULL_NODE_INDEX;
	int leftChildIndex1 = nodeIndex1 != NULL_NODE_INDEX ? this->mKDTreeNodes[nodeIndex1].mLeftNode : NULL_NODE_INDEX;
	int rightChildIndex1 = nodeIndex1 != NULL_NODE_INDEX ? this->mKDTreeNodes[nodeIndex1].mRightNode : NULL_NODE_INDEX;

	int parentIndex2 = nodeIndex2 != NULL_NODE_INDEX ? this->mKDTreeNodes[nodeIndex2].mParentIndex : NULL_NODE_INDEX;
	int leftChildIndex2 = nodeIndex2 != NULL_NODE_INDEX ? this->mKDTreeNodes[nodeIndex2].mLeftNode : NULL_NODE_INDEX;
	int rightChildIndex2 = nodeIndex2 != NULL_NODE_INDEX ? this->mKDTreeNodes[nodeIndex2].mRightNode : NULL_NODE_INDEX;

	if (parentIndex1 != NULL_NODE_INDEX)
	{
		if (this->mKDTreeNodes[parentIndex1].mLeftNode == nodeIndex1)
		{
			this->mKDTreeNodes[parentIndex1].mLeftNode = nodeIndex2;
		}
		else if (this->mKDTreeNodes[parentIndex1].mRightNode == nodeIndex1)
		{
			this->mKDTreeNodes[parentIndex1].mRightNode = nodeIndex2;
		}
		else
		{
			NEVER_HAPPEN;
		}
	}
	
	if (parentIndex2 != NULL_NODE_INDEX)
	{
		if (this->mKDTreeNodes[parentIndex2].mLeftNode == nodeIndex2)
		{
			this->mKDTreeNodes[parentIndex2].mLeftNode = nodeIndex1;
		}
		else if (this->mKDTreeNodes[parentIndex2].mRightNode == nodeIndex2)
		{
			this->mKDTreeNodes[parentIndex2].mRightNode = nodeIndex1;
		}
		else
		{
			NEVER_HAPPEN;
		}
	}


	if (leftChildIndex1 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[leftChildIndex1].mParentIndex = nodeIndex2;
	}
	if (rightChildIndex1 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[rightChildIndex1].mParentIndex = nodeIndex2;
	}

	if (leftChildIndex2 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[leftChildIndex2].mParentIndex = nodeIndex1;
	}
	if (rightChildIndex2 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[rightChildIndex2].mParentIndex = nodeIndex1;
	}
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