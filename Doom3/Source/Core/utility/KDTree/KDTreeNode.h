#pragma once

#include "KDTreeCore.h"

#include <Vector2.h>
#include <Vector3.h>

#include "../TreeNode.h"

namespace doom
{
	template <typename T>
	struct KDTreeNode : public TreeNode
	{
		friend class KDTree<T>;
		friend class KDTree_TestRoom;
		friend class KDTreeNodeView<T>;

		using component_type = typename T;

		T mComponentValue;

	
		INT32 mDimension{ NULL_NODE_INDEX };

		
	};

	using KDTreeNode2DPoint = typename KDTree<math::Vector2>;
	using KDTreeNode3DPoint = typename KDTree<math::Vector3>;
	//using KDTreeNodeAABB3D = typename KDTree<physics::AABB3D>;

}