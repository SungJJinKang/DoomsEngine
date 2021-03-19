#pragma once

#include "Core.h"

#include <queue>

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
	template <int Dimension>
	class KDTree
	{
		using node_type = typename KDTreeNode<Dimension>;
		using node_view_type = typename KDTreeNodeView<Dimension>;

	private:
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

		int AllocateNode(const typename node_type::component_type & point);
		void FreeNode(int index);

		int _Insert(const typename node_type::component_type & point, int searchIndex, int parentIndex, const int searchDimension);
		int _FineMin(const int index, const int searchDimension, const int targetMinNodeDimension);
		int _Delete(const typename node_type::component_type& point, int searchIndex, int parentIndex, const int searchDimension, const int targetMinNodeDimension);

	public:
		KDTree(int capacity);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="vector"></param>
		/// <returns>node index</returns>
		node_view_type Insert(const typename node_type::component_type& point);
		node_view_type Insert(const typename node_type::component_type& point, const int searchIndex, const int searchDimension);
		void Delete(const typename node_type::component_type& vector);
		void Delete(int nodeIndex);

		node_view_type FineMin(const int targetMinNodeDimension);

		constexpr node_view_type MakeKDTree_Node_View(int index)
		{
			D_ASSERT(index < this->mNodeCapacity);
			return node_view_type(&(this->mKDTreeNodes), index);
		}
	};

	using KDTree_2D = typename KDTree<2>;
	using KDTree_3D = typename KDTree<3>;
	
	extern template class KDTree<2>;
	extern template class KDTree<3>;
}
