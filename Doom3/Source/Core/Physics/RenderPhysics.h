#pragma once
#include "../Graphics/Color.h"
namespace doom
{
	namespace physics
	{
		class RenderPhysics
		{
			friend class Physics_server;
		protected:
			virtual void Render(eColor color) = 0;
		public:
			void DrawPhysicsDebug();
		};
	}
}