#include "KDTree.h"



template<typename T>
int doom::KDTree<T>::AllocateNode(const typename node_type::component_type& componentValue)
{
	int newNodeIndex;
	if (mFreedNodeIndexList.empty() == false)
	{// if there is freedNode
		newNodeIndex = mFreedNodeIndexList.front();
		mFreedNodeIndexList.pop();
	}
	else
	{
		mCurrentAllocatedNodeCount++;

		D_ASSERT(mCurrentAllocatedNodeCount <= mNodeCapacity);

		newNodeIndex = mCurrentAllocatedNodeCount - 1;
	}

	mCurrentActiveNodeCount++;

	mKDTreeNodes[newNodeIndex].mComponentValue = componentValue;
	mKDTreeNodes[newNodeIndex].mIndex = newNodeIndex;
	mKDTreeNodes[newNodeIndex].bmIsActive = true;

	return newNodeIndex;
}

template<typename T>
void doom::KDTree<T>::FreeNode(const int index)
{
	D_ASSERT(index != NULL_NODE_INDEX);

	int parentIndex = mKDTreeNodes[index].mParentIndex;
	if (parentIndex != NULL_NODE_INDEX)
	{
		if (mKDTreeNodes[parentIndex].mLeftNode == index)
		{
			mKDTreeNodes[parentIndex].mLeftNode = NULL_NODE_INDEX;
		}
		else if (mKDTreeNodes[parentIndex].mRightNode == index)
		{
			mKDTreeNodes[parentIndex].mRightNode = NULL_NODE_INDEX;
		}
		else
		{
			NEVER_HAPPEN;
		}
	}

	int leftNodeIndex = mKDTreeNodes[index].mLeftNode;
	if (leftNodeIndex != NULL_NODE_INDEX)
	{
		mKDTreeNodes[leftNodeIndex].mParentIndex = NULL_NODE_INDEX;
	}

	int rightNodeIndex = mKDTreeNodes[index].mRightNode;
	if (rightNodeIndex != NULL_NODE_INDEX)
	{
		mKDTreeNodes[rightNodeIndex].mParentIndex = NULL_NODE_INDEX;
	}

	mKDTreeNodes[index].mIndex = NULL_NODE_INDEX;
	mKDTreeNodes[index].mBitFlag = 0;
	mKDTreeNodes[index].bmIsActive = false;
	mKDTreeNodes[index].mParentIndex = NULL_NODE_INDEX;
	mKDTreeNodes[index].mLeftNode = NULL_NODE_INDEX;
	mKDTreeNodes[index].mRightNode = NULL_NODE_INDEX;

	mCurrentActiveNodeCount--;
	mFreedNodeIndexList.push(index);
}

template<typename T>
int doom::KDTree<T>::_Insert(const typename node_type::component_type & componentValue, int searchIndex, int parentIndex, const int searchDimension, int& insertedIndex)
{
	if (searchIndex == NULL_NODE_INDEX)
	{// find empty node
		//create inserted node
		searchIndex = AllocateNode(componentValue);
		mKDTreeNodes[searchIndex].mDimension = searchDimension;
		mKDTreeNodes[searchIndex].mParentIndex = parentIndex;

		insertedIndex = searchIndex;
	}
	else if (componentValue == mKDTreeNodes[searchIndex].mComponentValue)
	{// when equal
		NEVER_HAPPEN;
	}
	else if (componentValue[searchDimension] < mKDTreeNodes[searchIndex].mComponentValue[searchDimension])
	{
		int childIndex = _Insert(componentValue, mKDTreeNodes[searchIndex].mLeftNode, searchIndex, (searchDimension + 1) % GetDimensionCount(), insertedIndex);
		_PutChildNode(searchIndex, childIndex, true);
	}
	else
	{
		int childIndex = _Insert(componentValue, mKDTreeNodes[searchIndex].mRightNode, searchIndex, (searchDimension + 1) % GetDimensionCount(), insertedIndex);
		_PutChildNode(searchIndex, childIndex, false);
	}
	
	return searchIndex;
}

template<typename T>
int doom::KDTree<T>::_FineMin(const int index, const int searchDimension, const int targetMinNodeT)
{
	int minNode{ NULL_NODE_INDEX };
	
	int nextSearchDimension = (searchDimension + 1) % GetDimensionCount();

	if (index == NULL_NODE_INDEX)
	{
		return NULL_NODE_INDEX;
	}
	else if (searchDimension == targetMinNodeT)
	{
		minNode = index;
		if (mKDTreeNodes[index].mLeftNode != NULL_NODE_INDEX)
		{
			minNode = _FineMin(mKDTreeNodes[index].mLeftNode, nextSearchDimension, targetMinNodeT);
		}
		return minNode;
	}
	else
	{
		minNode = NULL_NODE_INDEX;
		int minLeft = _FineMin(mKDTreeNodes[index].mLeftNode, nextSearchDimension, targetMinNodeT);
		int minRigth = _FineMin(mKDTreeNodes[index].mRightNode, nextSearchDimension, targetMinNodeT);

		if (minLeft != NULL_NODE_INDEX && minRigth != NULL_NODE_INDEX)
		{
			if (mKDTreeNodes[minLeft].mComponentValue[searchDimension] < mKDTreeNodes[minRigth].mComponentValue[searchDimension])
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
			if (mKDTreeNodes[index].mComponentValue[searchDimension] < mKDTreeNodes[minNode].mComponentValue[searchDimension])
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
	int nextT = (searchT + 1) % GetDimensionCount();
	if (searchIndex == NULL_NODE_INDEX)
	{
		NEVER_HAPPEN;
	}
	else if (mKDTreeNodes[searchIndex].mComponentValue == componentValue)
	{
		if (mKDTreeNodes[searchIndex].mRightNode != NULL_NODE_INDEX)
		{
			//swap searchcomponentValue Node with right min node
			int replacedNodeIndex = _FineMin(mKDTreeNodes[searchIndex].mRightNode, nextT, searchT);
			_SwapNode(searchIndex, replacedNodeIndex);

			//searchIndex will be removed
			mKDTreeNodes[searchIndex].mComponentValue = mKDTreeNodes[replacedNodeIndex].mComponentValue;

			//delete replaced ndoe
			int rightNodeIndex = _Delete(mKDTreeNodes[searchIndex].mComponentValue, mKDTreeNodes[replacedNodeIndex].mRightNode, searchIndex, nextT);
			_PutChildNode(searchIndex, rightNodeIndex, false); // put as right child
		}
		else if (mKDTreeNodes[searchIndex].mLeftNode != NULL_NODE_INDEX)
		{
			//swap searchcomponentValue Node with left min node
			int replacedNodeIndex = _FineMin(mKDTreeNodes[searchIndex].mLeftNode, nextT, searchT);
			_SwapNode(searchIndex, replacedNodeIndex);

			//searchIndex will be removed
			mKDTreeNodes[searchIndex].mComponentValue = mKDTreeNodes[replacedNodeIndex].mComponentValue;

			//delete replaced ndoe
			int leftNodeIndex = _Delete(mKDTreeNodes[searchIndex].mComponentValue, mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextT);
			_PutChildNode(searchIndex, leftNodeIndex, false); // put as right child
		}
		else
		{// searchIndex don't have child
			FreeNode(searchIndex);
			searchIndex = NULL_NODE_INDEX;
		}
		

		

	}
	else if (componentValue[searchT] < mKDTreeNodes[searchIndex].mComponentValue[searchT])
	{
		int leftNodeIndex = _Delete(componentValue, mKDTreeNodes[searchIndex].mLeftNode, searchIndex, nextT);
		_PutChildNode(searchIndex, leftNodeIndex, true);
	}
	else
	{
		int rightNodeIndex = _Delete(componentValue, mKDTreeNodes[searchIndex].mRightNode, searchIndex, nextT);
		_PutChildNode(searchIndex, rightNodeIndex, false);
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

	int parentIndex1 = nodeIndex1 != NULL_NODE_INDEX ? mKDTreeNodes[nodeIndex1].mParentIndex : NULL_NODE_INDEX;
	int leftChildIndex1 = nodeIndex1 != NULL_NODE_INDEX ? mKDTreeNodes[nodeIndex1].mLeftNode : NULL_NODE_INDEX;
	int rightChildIndex1 = nodeIndex1 != NULL_NODE_INDEX ? mKDTreeNodes[nodeIndex1].mRightNode : NULL_NODE_INDEX;

	int parentIndex2 = nodeIndex2 != NULL_NODE_INDEX ? mKDTreeNodes[nodeIndex2].mParentIndex : NULL_NODE_INDEX;
	int leftChildIndex2 = nodeIndex2 != NULL_NODE_INDEX ? mKDTreeNodes[nodeIndex2].mLeftNode : NULL_NODE_INDEX;
	int rightChildIndex2 = nodeIndex2 != NULL_NODE_INDEX ? mKDTreeNodes[nodeIndex2].mRightNode : NULL_NODE_INDEX;

	if (parentIndex1 != NULL_NODE_INDEX)
	{
		if (mKDTreeNodes[parentIndex1].mLeftNode == nodeIndex1)
		{
			mKDTreeNodes[parentIndex1].mLeftNode = nodeIndex2;
		}
		else if (mKDTreeNodes[parentIndex1].mRightNode == nodeIndex1)
		{
			mKDTreeNodes[parentIndex1].mRightNode = nodeIndex2;
		}
		else
		{
			NEVER_HAPPEN;
		}
	}
	mKDTreeNodes[nodeIndex2].mParentIndex = parentIndex1;
	
	if (parentIndex2 != NULL_NODE_INDEX)
	{
		if (mKDTreeNodes[parentIndex2].mLeftNode == nodeIndex2)
		{
			mKDTreeNodes[parentIndex2].mLeftNode = nodeIndex1;
		}
		else if (mKDTreeNodes[parentIndex2].mRightNode == nodeIndex2)
		{
			mKDTreeNodes[parentIndex2].mRightNode = nodeIndex1;
		}
		else
		{
			NEVER_HAPPEN;
		}
	}
	mKDTreeNodes[nodeIndex1].mParentIndex = parentIndex2;

	if (leftChildIndex1 != NULL_NODE_INDEX)
	{
		mKDTreeNodes[leftChildIndex1].mParentIndex = nodeIndex2;
	}
	mKDTreeNodes[nodeIndex2].mLeftNode = leftChildIndex1;

	if (rightChildIndex1 != NULL_NODE_INDEX)
	{
		mKDTreeNodes[rightChildIndex1].mParentIndex = nodeIndex2;
	}
	mKDTreeNodes[nodeIndex2].mRightNode = rightChildIndex1;

	if (leftChildIndex2 != NULL_NODE_INDEX)
	{
		mKDTreeNodes[leftChildIndex2].mParentIndex = nodeIndex1;
	}
	mKDTreeNodes[nodeIndex1].mLeftNode = leftChildIndex2;

	if (rightChildIndex2 != NULL_NODE_INDEX)
	{
		mKDTreeNodes[rightChildIndex2].mParentIndex = nodeIndex1;
	}
	mKDTreeNodes[nodeIndex1].mRightNode = rightChildIndex2;
}

template<typename T>
void doom::KDTree<T>::_PutChildNode(int parentIndex, int childIndex, bool isLeftNode)
{
	D_ASSERT(parentIndex != NULL_NODE_INDEX || childIndex != NULL_NODE_INDEX);

	if (parentIndex != NULL_NODE_INDEX)
	{
		if (isLeftNode == true)
		{
			mKDTreeNodes[parentIndex].mLeftNode = childIndex;
		}
		else
		{
			mKDTreeNodes[parentIndex].mRightNode = childIndex;
		}
	}

	if (childIndex != NULL_NODE_INDEX)
	{
		mKDTreeNodes[childIndex].mParentIndex = parentIndex;
	}	
}

template<typename T>
doom::KDTree<T>::KDTree(int capacity)
	:mNodeCapacity{ capacity }
{
	mKDTreeNodes = new KDTreeNode<T>[capacity]();
}

template<typename T>
typename doom::KDTree<T>::node_view_type doom::KDTree<T>::Insert(const typename node_type::component_type& componentValue)
{
	int newNodexIndex = NULL_NODE_INDEX;
	if (mRootNodeIndex == NULL_NODE_INDEX)
	{
		newNodexIndex = AllocateNode(componentValue);
		mRootNodeIndex = newNodexIndex;
		return MakeKDTree_Node_View(newNodexIndex);
	}

	_Insert(componentValue, mRootNodeIndex, NULL_NODE_INDEX, 0, newNodexIndex);

	return MakeKDTree_Node_View(newNodexIndex);
}

template<typename T>
void doom::KDTree<T>::Delete(const typename node_type::component_type& componentValue)
{
	if(mRootNodeIndex == NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("There is no RootNode", eLogType::D_WARNING);
		return;
	}
	_Delete(componentValue, mRootNodeIndex, NULL_NODE_INDEX, 0);
}

template<typename T>
void doom::KDTree<T>::Delete(int nodeIndex)
{
}

template<typename T>
typename doom::KDTree<T>::node_view_type doom::KDTree<T>::FineMin(const unsigned int targetMinNodeDimension)
{
	D_ASSERT(targetMinNodeDimension >= 0 && targetMinNodeDimension < GetDimensionCount());
	if (mRootNodeIndex == NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("There is no RootNode", eLogType::D_WARNING);
		return MakeKDTree_Node_View(NULL_NODE_INDEX);
	}
	int minNodeIndex = _FineMin(mRootNodeIndex, 0, targetMinNodeDimension);
	return MakeKDTree_Node_View(minNodeIndex);
}



//template class doom::KDTree<math::Vector2>;
//template class doom::KDTree<doom::physics::AABB3D>;

template class doom::KDTree<math::Vector3>;
template struct doom::KDTreeNode<math::Vector3>;
template class doom::KDTreeNodeView<math::Vector3>;