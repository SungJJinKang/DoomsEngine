#include "KDTree.h"



template<typename T>
int doom::KDTree<T>::AllocateNode(const typename node_type::component_type& componentValue)
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

	this->mKDTreeNodes[newNodeIndex].mComponentValue = componentValue;
	this->mKDTreeNodes[newNodeIndex].mIndex = newNodeIndex;
	this->mKDTreeNodes[newNodeIndex].bmIsActive = true;

	return newNodeIndex;
}

template<typename T>
void doom::KDTree<T>::FreeNode(const int index)
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
	this->mKDTreeNodes[index].mBitFlag = 0;
	this->mKDTreeNodes[index].bmIsActive = false;
	this->mKDTreeNodes[index].mParentIndex = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].mLeftNode = NULL_NODE_INDEX;
	this->mKDTreeNodes[index].mRightNode = NULL_NODE_INDEX;

	this->mCurrentActiveNodeCount--;
	this->mFreedNodeIndexList.push(index);
}

template<typename T>
int doom::KDTree<T>::_Insert(const typename node_type::component_type & componentValue, int searchIndex, int parentIndex, const int searchDimension, int& insertedIndex)
{
	if (searchIndex == NULL_NODE_INDEX)
	{// find empty node
		//create inserted node
		searchIndex = this->AllocateNode(componentValue);
		this->mKDTreeNodes[searchIndex].mDimension = searchDimension;
		this->mKDTreeNodes[searchIndex].mParentIndex = parentIndex;

		insertedIndex = searchIndex;
	}
	else if (componentValue == this->mKDTreeNodes[searchIndex].mComponentValue)
	{// when equal
		NEVER_HAPPEN;
	}
	else if (componentValue[searchDimension] < this->mKDTreeNodes[searchIndex].mComponentValue[searchDimension])
	{
		int childIndex = _Insert(componentValue, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, (searchDimension + 1) % this->GetDimensionCount(), insertedIndex);
		this->_PutChildNode(searchIndex, childIndex, true);
	}
	else
	{
		int childIndex = _Insert(componentValue, this->mKDTreeNodes[searchIndex].mRightNode, searchIndex, (searchDimension + 1) % this->GetDimensionCount(), insertedIndex);
		this->_PutChildNode(searchIndex, childIndex, false);
	}
	
	return searchIndex;
}

template<typename T>
int doom::KDTree<T>::_FineMin(const int index, const int searchDimension, const int targetMinNodeT)
{
	int minNode{ NULL_NODE_INDEX };
	
	int nextSearchDimension = (searchDimension + 1) % this->GetDimensionCount();

	if (index == NULL_NODE_INDEX)
	{
		return NULL_NODE_INDEX;
	}
	else if (searchDimension == targetMinNodeT)
	{
		minNode = index;
		if (this->mKDTreeNodes[index].mLeftNode != NULL_NODE_INDEX)
		{
			minNode = this->_FineMin(this->mKDTreeNodes[index].mLeftNode, nextSearchDimension, targetMinNodeT);
		}
		return minNode;
	}
	else
	{
		minNode = NULL_NODE_INDEX;
		int minLeft = _FineMin(this->mKDTreeNodes[index].mLeftNode, nextSearchDimension, targetMinNodeT);
		int minRigth = _FineMin(this->mKDTreeNodes[index].mRightNode, nextSearchDimension, targetMinNodeT);

		if (minLeft != NULL_NODE_INDEX && minRigth != NULL_NODE_INDEX)
		{
			if (this->mKDTreeNodes[minLeft].mComponentValue[searchDimension] < this->mKDTreeNodes[minRigth].mComponentValue[searchDimension])
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
			if (this->mKDTreeNodes[index].mComponentValue[searchDimension] < this->mKDTreeNodes[minNode].mComponentValue[searchDimension])
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

template<typename T>
int doom::KDTree<T>::_Delete(const typename node_type::component_type& componentValue, int searchIndex, const int parentIndex, const int searchT)
{
	int nextT = (searchT + 1) % this->GetDimensionCount();
	if (searchIndex == NULL_NODE_INDEX)
	{
		NEVER_HAPPEN;
	}
	else if (this->mKDTreeNodes[searchIndex].mComponentValue == componentValue)
	{
		if (this->mKDTreeNodes[searchIndex].mRightNode != NULL_NODE_INDEX)
		{
			//swap searchcomponentValue Node with right min node
			int replacedNodeIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mRightNode, nextT, searchT);
			this->_SwapNode(searchIndex, replacedNodeIndex);

			//searchIndex will be removed
			this->mKDTreeNodes[searchIndex].mComponentValue = this->mKDTreeNodes[replacedNodeIndex].mComponentValue;

			//delete replaced ndoe
			int rightNodeIndex = this->_Delete(this->mKDTreeNodes[searchIndex].mComponentValue, this->mKDTreeNodes[replacedNodeIndex].mRightNode, searchIndex, nextT);
			this->_PutChildNode(searchIndex, rightNodeIndex, false); // put as right child
		}
		else if (this->mKDTreeNodes[searchIndex].mLeftNode != NULL_NODE_INDEX)
		{
			//swap searchcomponentValue Node with left min node
			int replacedNodeIndex = this->_FineMin(this->mKDTreeNodes[searchIndex].mLeftNode, nextT, searchT);
			this->_SwapNode(searchIndex, replacedNodeIndex);

			//searchIndex will be removed
			this->mKDTreeNodes[searchIndex].mComponentValue = this->mKDTreeNodes[replacedNodeIndex].mComponentValue;

			//delete replaced ndoe
			int leftNodeIndex = this->_Delete(this->mKDTreeNodes[searchIndex].mComponentValue, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextT);
			this->_PutChildNode(searchIndex, leftNodeIndex, false); // put as right child
		}
		else
		{// searchIndex don't have child
			this->FreeNode(searchIndex);
			searchIndex = NULL_NODE_INDEX;
		}
		

		

	}
	else if (componentValue[searchT] < this->mKDTreeNodes[searchIndex].mComponentValue[searchT])
	{
		int leftNodeIndex = this->_Delete(componentValue, this->mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextT);
		this->_PutChildNode(searchIndex, leftNodeIndex, true);
	}
	else
	{
		int rightNodeIndex = this->_Delete(componentValue, this->mKDTreeNodes[searchIndex].mRightNode, searchIndex, nextT);
		this->_PutChildNode(searchIndex, rightNodeIndex, false);
	}

	return searchIndex;
}

template <typename T>
void doom::KDTree<T>::_SwapNode(int nodeIndex1, int nodeIndex2)
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

template<typename T>
void doom::KDTree<T>::_PutChildNode(int parentIndex, int childIndex, bool isLeftNode)
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

template<typename T>
doom::KDTree<T>::KDTree(int capacity)
	:mNodeCapacity{ capacity }
{
	this->mKDTreeNodes = new KDTreeNode<T>[capacity]();
}

template<typename T>
typename doom::KDTree<T>::node_view_type doom::KDTree<T>::Insert(const typename node_type::component_type& componentValue)
{
	int newNodexIndex = NULL_NODE_INDEX;
	if (this->mRootNodeIndex == NULL_NODE_INDEX)
	{
		newNodexIndex = this->AllocateNode(componentValue);
		this->mRootNodeIndex = newNodexIndex;
		return this->MakeKDTree_Node_View(newNodexIndex);
	}

	this->_Insert(componentValue, this->mRootNodeIndex, NULL_NODE_INDEX, 0, newNodexIndex);

	return this->MakeKDTree_Node_View(newNodexIndex);
}

template<typename T>
void doom::KDTree<T>::Delete(const typename node_type::component_type& componentValue)
{
	if(this->mRootNodeIndex == NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("There is no RootNode", eLogType::D_WARNING);
		return;
	}
	this->_Delete(componentValue, this->mRootNodeIndex, NULL_NODE_INDEX, 0);
}

template<typename T>
void doom::KDTree<T>::Delete(int nodeIndex)
{
}

template<typename T>
typename doom::KDTree<T>::node_view_type doom::KDTree<T>::FineMin(const unsigned int targetMinNodeDimension)
{
	D_ASSERT(targetMinNodeDimension >= 0 && targetMinNodeDimension < this->GetDimensionCount());
	if (this->mRootNodeIndex == NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("There is no RootNode", eLogType::D_WARNING);
		return this->MakeKDTree_Node_View(NULL_NODE_INDEX);
	}
	int minNodeIndex = this->_FineMin(this->mRootNodeIndex, 0, targetMinNodeDimension);
	return this->MakeKDTree_Node_View(minNodeIndex);
}



template class doom::KDTree<math::Vector2>;
template class doom::KDTree<math::Vector3>;
//template class doom::KDTree<doom::physics::AABB3D>;