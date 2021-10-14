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

		static UINT32 GetDimensionCount();

		node_type* mKDTreeNodes;
		const INT32 mNodeCapacity;

		INT32 mRootNodeIndex{ NULL_NODE_INDEX };

		/// <summary>
		/// Ever used Node Count
		/// this value contain freed node count
		/// </summary>
		INT32 mCurrentAllocatedNodeCount{ 0 };
		/// <summary>
		/// Current used node count
		/// this value doesn't contain freed node count
		/// </summary>
		INT32 mCurrentActiveNodeCount{ 0 };
		/// <summary>
		/// if you want parallel access, Use concurrentQueue
		/// </summary>
		std::queue<INT32> mFreedNodeIndexList{};

		INT32 AllocateNode(const typename node_type::component_type & componentValue);
		void FreeNode(const INT32 index);

		INT32 _Insert(const typename node_type::component_type & componentValue, INT32 searchIndex, INT32 parentIndex, const INT32 searchDimension, INT32& insertedIndex);
		INT32 _FineMin(const INT32 index, const INT32 searchDimension, const INT32 targetMinNodeDimension);
		INT32 _Delete(const typename node_type::component_type& componentValue, INT32 searchIndex, const INT32 parentIndex, const INT32 searchDimension);
		void _SwapNode(INT32 nodeIndex1, INT32 nodeIndex2);
		void _PutChildNode(INT32 parentIndex, INT32 childIndex, bool isLeftNode);

	public:
		KDTree(INT32 capacity);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="vector"></param>
		/// <returns>node index</returns>
		node_view_type Insert(const typename node_type::component_type& componentValue);
		//node_view_type Insert(const typename node_type::component_type& componentValue, const INT32 searchIndex, const INT32 searchDimension);
		void Delete(const typename node_type::component_type& vector);
		void Delete(INT32 nodeIndex);

		node_view_type FineMin(const UINT32 targetMinNodeDimension);

		/// <summary>
		/// Only used when type T is Vector
		/// https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf 15page
		/// </summary>
		/// <param name="targetMinNodeDimension"></param>
		/// <returns></returns>
		node_view_type FindNearestNode(const typename node_type::component_type& componentValue);

		node_view_type MakeKDTree_Node_View(INT32 index)
		{
			D_ASSERT(index < mCurrentAllocatedNodeCount);
			return node_view_type(this, index);
		}

	
	};

	/*template <>
	inline static UINT32 KDTree<math::Vector2>::GetDimensionCount()
	{
		return 2;
	}*/
	template <>
	inline static UINT32 KDTree<math::Vector3>::GetDimensionCount()
	{
		return 3;
	}
	/*template <>
	inline static UINT32 KDTree<physics::AABB3D>::GetDimensionCount()
	{
		return 3;
	}*/

	//using KDTree2DPoint = typename KDTree<math::Vector2>;
	using KDTree3DPoint = typename KDTree<math::Vector3>;
	//using KDTreeAABB3D = typename KDTree<physics::AABB3D>;
	
	//extern template class KDTree<math::Vector2>;
	
	//extern template class KDTree<physics::AABB3D>;


}

extern template class doom::KDTree<math::Vector3>;
extern template struct doom::KDTreeNode<math::Vector3>;
extern template class doom::KDTreeNodeView<math::Vector3>;