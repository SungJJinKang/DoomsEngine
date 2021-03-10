#pragma once
#include "../BVH.h"

namespace doom
{
	namespace physics
	{
		class BVH_TestRoom
		{
		private:
			BVH3D mBVH{};

			void AddNewRandomLeafNode();
			
		public:

			void Update();
		};
	}
}

