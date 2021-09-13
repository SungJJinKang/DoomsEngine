#pragma once

#include "Core.h"

#include <queue>

#include "Physics/Collider/AABB.h"
#include <Vector2.h>
#include <Vector3.h>

#include "KDTreeCore.h"
#include "KDTreeNode.h"
#include "KDTreeNodeView.h"

namespace doom
{

	/// <summary>
	/// reference : 
	/// https://towardsdatascience.com/understanding-k-dimensional-trees-1cdbf6075f22
	/// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf
	/// </summary>
	template <typename T>
	class KDTree
	{
		friend class KDTree_TestRoom;
		friend class KDTreeNodeView<T>;

		using node_type = typename KDTreeNode<T>;
		using node_view_type = typename KDTreeNodeView<T>;
		
	private:

		static unsigned int GetDimensionCount();

		node_type* mKDTreeNodes;
		const int mNodeCapacity;

		int mRootNodeIndex{ NULL_NODE_INDEX };

		/// <summary>
		/// Ever used Node Count
		/// this value contain freed node count
		/// </summary>
		int mCurrentAllocatedNodeCount{ 0 };
		/// <summary>
		/// Current used node count
		/// this value doesn't contain freed node count
		/// </summary>
		int mCurrentActiveNodeCount{ 0 };
		/// <summary>
		/// if you want parallel access, Use concurrentQueue
		/// </summary>
		std::queue<int> mFreedNodeIndexList{};

		int AllocateNode(const typename node_type::component_type & componentValue);
		void FreeNode(const int index);

		int _Insert(const typename node_type::component_type & componentValue, int searchIndex, int parentIndex, const int searchDimension, int& insertedIndex);
		int _FineMin(const int index, const int searchDimension, const int targetMinNodeDimension);
		int _Delete(const typename node_type::component_type& componentValue, int searchIndex, const int parentIndex, const int searchDimension);
		void _SwapNode(int nodeIndex1, int nodeIndex2);
		void _PutChildNode(int parentIndex, int childIndex, bool isLeftNode);

	public:
		KDTree(int capacity);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="vector"></param>
		/// <returns>node index</returns>
		node_view_type Insert(const typename node_type::component_type& componentValue);
		//node_view_type Insert(const typename node_type::component_type& componentValue, const int searchIndex, const int searchDimension);
		void Delete(const typename node_type::component_type& vector);
		void Delete(int nodeIndex);

		node_view_type FineMin(const unsigned int targetMinNodeDimension);

		/// <summary>
		/// Only used when type T is Vector
		/// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf 15page
		/// </summary>
		/// <param name="targetMinNodeDimension"></param>
		/// <returns></returns>
		node_view_type FindNearestNode(const typename node_type::component_type& componentValue);

		node_view_type MakeKDTree_Node_View(int index)
		{
			D_ASSERT(index < mCurrentAllocatedNodeCount);
			return node_view_type(this, index);
		}

	
	};

	template <>
	inline static unsigned int KDTree<math::Vector2>::GetDimensionCount()
	{
		return 2;
	}
	template <>
	inline static unsigned int KDTree<math::Vector3>::GetDimensionCount()
	{
		return 3;
	}
	template <>
	inline static unsigned int KDTree<physics::AABB3D>::GetDimensionCount()
	{
		return 3;
	}

	using KDTree2DPoint = typename KDTree<math::Vector2>;
	using KDTree3DPoint = typename KDTree<math::Vector3>;
	//using KDTreeAABB3D = typename KDTree<physics::AABB3D>;
	
	extern template class KDTree<math::Vector2>;
	extern template class KDTree<math::Vector3>;
	//extern template class KDTree<physics::AABB3D>;
}
