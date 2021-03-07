#include "RenderPhysics.h"
#include "Physics_Server.h"
#include "../Graphics/DebugGraphics.h"
#include <MainTimer.h>



void doom::physics::RenderPhysics::DrawPhysicsDebugColor(eColor color)
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
