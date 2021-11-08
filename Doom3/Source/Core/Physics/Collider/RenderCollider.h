#pragma once

#include "Core.h"
#include <Graphics/Graphics_Core.h>
#include <Graphics/Color.h>

namespace dooms
{
	namespace physics
	{
		class DOOM_API D_CLASS RenderCollider
		{
		private:

			UINT64 mLastRenderFrameTickCount{};

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