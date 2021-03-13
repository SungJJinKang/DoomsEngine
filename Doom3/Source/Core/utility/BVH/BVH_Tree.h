#pragma once
#include <queue>
#include <memory>

#include "Physics/Collider/AABB.h"
#include "BVH_Node.h"

namespace doom
{
	namespace physics
	{
		class BVH_TestRoom;
	}

	template <typename AABB>
	class BVH;

	template <typename AABB>
	class BVH_Node;

	/// <summary>
	/// 
	/// </summary>
	template <typename AABB>
	class BVH_Tree
	{
		friend class BVH<AABB>;
		friend class BVH_Node<AABB>;
		friend class doom::physics::BVH_TestRoom;

	private:

		/// <summary>
		/// array
		/// Never pop inserted node
		/// Just make it dangling
		/// </summary>
		BVH_Node<AABB>* mNodes;
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
		std::queue<int> freedNodeIndexList{};

		BVH_Tree(int nodeCapacity);
		~BVH_Tree();

	public:

		BVH_Tree(const BVH_Tree&) = delete;
		BVH_Tree(BVH_Tree&&) noexcept = delete;
		BVH_Tree& operator=(const BVH_Tree&) = delete;
		BVH_Tree& operator=(BVH_Tree&&) noexcept = delete;
	};

	


	using BVH_Tree2D = typename BVH_Tree<doom::physics::AABB2D>;
	using BVH_Tree3D = typename BVH_Tree<doom::physics::AABB3D>;

	extern template class BVH_Tree<doom::physics::AABB2D>;
	extern template class BVH_Tree<doom::physics::AABB3D>;
}
