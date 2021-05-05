#pragma once
#include "../Graphics/Color.h"
#include "Core.h"
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
			virtual void Render(eColor color, bool drawInstantly = false) = 0;
		public:
			constexpr RenderPhysics() {}

#ifdef DEBUG_MODE
			virtual void DrawPhysicsDebug(bool drawInstantly = false) = 0;
			void DrawPhysicsDebugColor(eColor color, bool drawInstantly = false);
#endif
		};
	}
}