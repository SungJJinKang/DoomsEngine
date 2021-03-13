#pragma once

#include <memory>

#include "../BVH.h"

namespace doom
{
	namespace physics
	{
		class BVH_TestRoom
		{
		private:
			std::unique_ptr<BVH3D> mBVH;

			void AddNewRandomLeafNode();
			void AddNewRandomLeafNodeWithMouse();
			void RemoveRecentAddedLeafNode();
			void BalanceRecentAddedLeafNode();
			
		public:

			void SetBVH3D(BVH3D* bvh3D);
			void Update();
		};
	}
}

