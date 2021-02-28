#include "RenderPhysics.h"
#include "Physics_Server.h"
#include "../Graphics/DebugGraphics.h"
#include <MainTimer.h>

void doom::physics::RenderPhysics::DrawPhysicsDebug()
{
	doom::physics::RenderPhysics::DrawPhysicsDebug(graphics::DebugGraphics::mDefaultDebugColor);
}

void doom::physics::RenderPhysics::DrawPhysicsDebug(eColor color)
{
	if (Physics_Server::IsShowDebug == true)
	{
		//unsigned long long frameTickCount = MainTimer::GetCurrentFrameTime();

		//if (this->mLastRenderFrameTickCount != frameTickCount)
		//{
			Render(color);
		//}

		//this->mLastRenderFrameTickCount = frameTickCount;
	}
}
