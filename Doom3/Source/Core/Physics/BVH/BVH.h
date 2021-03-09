#pragma once

#include <type_traits>
#include "../Collider/AABB.h"
#include <stack>
#include <vector>

//BVH is used for rendering, collision detect, raycast, stero audio ......

namespace doom
{
	namespace physics
	{
		class Ray;

		struct Node
		{
			/// <summary>
			/// Node Bounding Box
			/// </summary>
			AABB3D mAABB;

			/// <summary>
			/// World Object Unqieu ID
			/// Will be used when mIsLeaf is true
			/// </summary>
			int mObjectIndex;

			/// <summary>
			/// Node Index in Tree::mNodes
			/// </summary>
			int mParentIndex;
			/// <summary>
			/// Node index in Tree::mNodes
			/// </summary>
			int mChild1;

			/// <summary>
			/// Node index in Tree::mNodes
			/// </summary>
			int mChild2;

			/// <summary>
			/// Is Leaf? = Is World Object?
			/// </summary>
			bool mIsLeaf;
		};
		
		struct Tree
		{
			/// <summary>
			/// array
			/// </summary>
			std::vector<Node> mNodes;

			/// <summary>
			/// NodeCount
			/// this is different with mNodes.size()
			/// </summary>
			int mNodeCount;

			/// <summary>
			/// Root Node Index in mNodes
			/// </summary>
			int mRootIndex;
		};

		class BVH
		{
		private:
			static bool TreeRayCast(Tree& tree, Ray& ray);


		};
	}
}
