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
void doom::KDTree<Dimension>::FreeNode(const int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);

	int parentIndex = this->mKDTreeNodes[index].mParentIndex;
	if (parentIndex != NULL_NODE_INDEX)
	{
		if (this->mKDTreeNodes[parentIndex].mLeftNode == index)
		{
			this->mKDTreeNodes[parentIndex].mLeftNode = NULL_NODE_INDEX;
		}
		else if (this->mKDTreeNodes[parentIndex].mRightNode == index)
		{
			this->mKDTreeNodes[parentIndex].mRightNode = NULL_NODE_INDEX;
		}
		else
		{
			NEVER_HAPPEN;
		}
	}

	int leftNodeIndex = this->mKDTreeNodes[index].mLeftNode;
	if (leftNodeIndex != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[leftNodeIndex].mParentIndex = NULL_NODE_INDEX;
	}

	int rightNodeIndex = this->mKDTreeNodes[index].mRightNode;
	if (rightNodeIndex != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[rightNodeIndex].mParentIndex = NULL_NODE_INDEX;
	}

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
int doom::KDTree<Dimension>::_Insert(const typename node_type::component_type & point, int searchIndex, int parentIndex, const int searchDimension, int& insertedIndex)
{
	if (searchIndex == NULL_NODE_INDEX)
	{// find empty node
		//create inserted node
		searchIndex = this->AllocateNode(point);
		this->mKDTreeNodes[searchIndex].mDimension = searchDimension;
		this->mKDTreeNodes[searchIndex].mParentIndex = parentIndex;

		insertedIndex = searchIndex;
	}
	else if (point == this->mKDTreeNodes[searchIndex].mPoint)
	{// when equal
		NEVER_HAPPEN;
	}
	else if (point[searchDimension] < this->mKDTreeNodes[searchIndex].mPoint[searchDimension])
	{
		int childIndex = _Insert(point, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, (searchDimension + 1) % Dimension, insertedIndex);
		this->_PutChildNode(searchIndex, childIndex, true);
	}
	else
	{
		int childIndex = _Insert(point, this->mKDTreeNodes[searchIndex].mRightNode, searchIndex, (searchDimension + 1) % Dimension, insertedIndex);
		this->_PutChildNode(searchIndex, childIndex, false);
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
int doom::KDTree<Dimension>::_Delete(const typename node_type::component_type& point, int searchIndex, const int parentIndex, const int searchDimension)
{
	int nextDimension = (searchDimension + 1) % Dimension;
	if (searchIndex == NULL_NODE_INDEX)
	{
		NEVER_HAPPEN;
	}
	else if (this->mKDTreeNodes[searchIndex].mPoint == point)
	{
		if (this->mKDTreeNodes[searchIndex].mRightNode != NULL_NODE_INDEX)
		{
			//swap searchpoint Node with right min node
			int replacedNodeIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mRightNode, nextDimension, searchDimension);
			this->_SwapNode(searchIndex, replacedNodeIndex);

			//searchIndex will be removed
			this->mKDTreeNodes[searchIndex].mPoint = this->mKDTreeNodes[replacedNodeIndex].mPoint;

			//delete replaced ndoe
			int rightNodeIndex = this->_Delete(this->mKDTreeNodes[searchIndex].mPoint, this->mKDTreeNodes[replacedNodeIndex].mRightNode, searchIndex, nextDimension);
			this->_PutChildNode(searchIndex, rightNodeIndex, false); // put as right child
		}
		else if (this->mKDTreeNodes[searchIndex].mLeftNode != NULL_NODE_INDEX)
		{
			//swap searchpoint Node with left min node
			int replacedNodeIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mLeftNode, nextDimension, searchDimension);
			this->_SwapNode(searchIndex, replacedNodeIndex);

			//searchIndex will be removed
			this->mKDTreeNodes[searchIndex].mPoint = this->mKDTreeNodes[replacedNodeIndex].mPoint;

			//delete replaced ndoe
			int leftNodeIndex = this->_Delete(this->mKDTreeNodes[searchIndex].mPoint, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextDimension);
			this->_PutChildNode(searchIndex, leftNodeIndex, false); // put as right child
		}
		else
		{// searchIndex don't have child
			this->FreeNode(searchIndex);
			searchIndex = NULL_NODE_INDEX;
		}
		

		

	}
	else if (point[searchDimension] < this->mKDTreeNodes[searchIndex].mPoint[searchDimension])
	{
		int leftNodeIndex = this->_Delete(point, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextDimension);
		this->_PutChildNode(searchIndex, leftNodeIndex, true);
	}
	else
	{
		int rightNodeIndex = this->_Delete(point, this->mKDTreeNodes[searchIndex].mRightNode, searchIndex, nextDimension);
		this->_PutChildNode(searchIndex, rightNodeIndex, false);
	}

	return searchIndex;
}

template <int Dimension>
void doom::KDTree<Dimension>::_SwapNode(int nodeIndex1, int nodeIndex2)
{
	if (nodeIndex1 == nodeIndex2)
	{
		return;
	}

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
	this->mKDTreeNodes[nodeIndex2].mParentIndex = parentIndex1;
	
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
	this->mKDTreeNodes[nodeIndex1].mParentIndex = parentIndex2;

	if (leftChildIndex1 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[leftChildIndex1].mParentIndex = nodeIndex2;
	}
	this->mKDTreeNodes[nodeIndex2].mLeftNode = leftChildIndex1;

	if (rightChildIndex1 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[rightChildIndex1].mParentIndex = nodeIndex2;
	}
	this->mKDTreeNodes[nodeIndex2].mRightNode = rightChildIndex1;

	if (leftChildIndex2 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[leftChildIndex2].mParentIndex = nodeIndex1;
	}
	this->mKDTreeNodes[nodeIndex1].mLeftNode = leftChildIndex2;

	if (rightChildIndex2 != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[rightChildIndex2].mParentIndex = nodeIndex1;
	}
	this->mKDTreeNodes[nodeIndex1].mRightNode = rightChildIndex2;
}

template<int Dimension>
void doom::KDTree<Dimension>::_PutChildNode(int parentIndex, int childIndex, bool isLeftNode)
{
	D_ASSERT(parentIndex != NULL_NODE_INDEX || childIndex != NULL_NODE_INDEX);

	if (parentIndex != NULL_NODE_INDEX)
	{
		if (isLeftNode == true)
		{
			this->mKDTreeNodes[parentIndex].mLeftNode = childIndex;
		}
		else
		{
			this->mKDTreeNodes[parentIndex].mRightNode = childIndex;
		}
	}

	if (childIndex != NULL_NODE_INDEX)
	{
		this->mKDTreeNodes[childIndex].mParentIndex = parentIndex;
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

	this->_Insert(point, this->mRootNodeIndex, NULL_NODE_INDEX, 0, newNodexIndex);

	return this->MakeKDTree_Node_View(newNodexIndex);
}

template<int Dimension>
void doom::KDTree<Dimension>::Delete(const typename node_type::component_type& point)
{
	if(this->mRootNodeIndex == NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("There is no RootNode", eLogType::D_WARNING);
		return;
	}
	this->_Delete(point, this->mRootNodeIndex, NULL_NODE_INDEX, 0);
}

template<int Dimension>
void doom::KDTree<Dimension>::Delete(int nodeIndex)
{
}

template<int Dimension>
typename doom::KDTree<Dimension>::node_view_type doom::KDTree<Dimension>::FineMin(const int targetMinNodeDimension)
{
	D_ASSERT(targetMinNodeDimension >= 0 && targetMinNodeDimension < Dimension);
	if (this->mRootNodeIndex == NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("There is no RootNode", eLogType::D_WARNING);
		return this->MakeKDTree_Node_View(NULL_NODE_INDEX);
	}
	int minNodeIndex = this->_FineMin(this->mRootNodeIndex, 0, targetMinNodeDimension);
	return this->MakeKDTree_Node_View(minNodeIndex);
}

template<int Dimension>
typename doom::KDTree<Dimension>::node_view_type doom::KDTree<Dimension>::FindNearestNode(const typename node_type::component_type& point)
{
	return node_view_type();
}






template class doom::KDTree<2>;
template class doom::KDTree<3>;