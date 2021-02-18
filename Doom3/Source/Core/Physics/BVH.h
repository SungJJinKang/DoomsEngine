#pragma once

#include <type_traits>
#include "AABB.h"
#include <stack>

namespace doom
{
	namespace physics
	{
		struct Node
		{
			AABB3D mAABB;
			int mObjectIndex;
			int mParentIndex;
			int mChild1;
			int mChild2;
			bool mIsLeaf;
		};
		
		struct Tree
		{
			Node* mNodes;
			int mNodeCount;
			int mRootIndex;
		};

		class BVH
		{
			static bool TreeRayCast(const Tree& tree, const AABB3D& aabb)
			{
				std::stack<int> stack{};
				stack.push(tree.mRootIndex);
				while (stack.empty() == false)
				{
					int index = stack.top();
					stack.pop();

					if (IsOverlap(tree.mNodes[index].mAABB, aabb) == false)
					{
						continue;
					}

					if (tree.mNodes[index].mIsLeaf)
					{
						int objectIndex = tree.mNodes[index].mObjectIndex;
						if()
					}
					else
					{
						stack.push(tree.mNodes[index].mChild1);
						stack.push(tree.mNodes[index].mChild2);
					}
				}
			}


		};
	}
}
