#pragma once

#include <Core.h>

namespace doom
{
	namespace physics
	{
		class PhysicsDebugger
		{

		private:

			void DrawMouseRayCast();

		public:

#ifdef DEBUG_MODE
			void UpdateDebugger()
			{
				DrawMouseRayCast();
			}
#else
			void UpdateDebugger()
			{
			}
#endif
		

		};
	}
}

