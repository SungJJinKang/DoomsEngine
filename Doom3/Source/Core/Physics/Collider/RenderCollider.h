#pragma once
#include "../Graphics/Color.h"
#include "Core.h"
namespace doom
{
	namespace physics
	{
		class RenderCollider
		{
		private:

			unsigned long long mLastRenderFrameTickCount{};

		protected:

			virtual void DrawCollider(eColor color, bool drawInstantly = false) = 0;

		public:

			constexpr RenderCollider() {}

#ifdef DEBUG_MODE
			void DrawPhysicsDebugColor(eColor color)
			{
				DrawCollider(color, false);
			}
#else
			void DrawPhysicsDebugColor(eColor color)
			{
			}
#endif

		};
	}
}