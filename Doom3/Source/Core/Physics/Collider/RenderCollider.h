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

			virtual void DrawCollider(eColor color, bool drawInstantly = false) const = 0;

		public:

			constexpr RenderCollider() {}

#ifdef DEBUG_DRAWER
			void DrawPhysicsDebugColor(eColor color) const
			{
				DrawCollider(color, false);
			}
#else
			void DrawPhysicsDebugColor(eColor color) const
			{
			}
#endif

		};
	}
}