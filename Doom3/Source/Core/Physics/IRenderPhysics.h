#pragma once
#include "Physics_Server.h"

namespace doom
{
	namespace physics
	{
		class IRenderPhysics
		{
			friend class Physics_server;
		protected:
			virtual void _DebugRender() = 0;
		public:
			void DebugRender()
			{
				if (Physics_Server::GetSingleton()->IsShowDebug == true)
				{
					_DebugRender();
				}
			}
		};
	}
}