#pragma once
#include "../Graphics/Color.h"
namespace doom
{
	namespace physics
	{
		class RenderPhysics
		{
			friend class Physics_server;
		private:
			unsigned long long mLastRenderFrameTickCount{};

		protected:
			virtual void Render(eColor color) = 0;
		public:
			void DrawPhysicsDebug();
			void DrawPhysicsDebug(eColor color);
		};
	}
}