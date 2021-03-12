#pragma once
#include "../BVH.h"

namespace doom
{
	namespace physics
	{
		class BVH_TestRoom
		{
		private:
			BVH2D mBVH{ 1000 };

			void AddNewRandomLeafNode();
			void RemoveRecentAddedLeafNode();
			
		public:

			void Update();
		};
	}
}

