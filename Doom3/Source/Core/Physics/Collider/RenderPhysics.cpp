#include "RenderPhysics.h"
#include "Physics_Server.h"
#include "../Graphics/DebugGraphics.h"
#include <MainTimer.h>



void doom::physics::RenderPhysics::DrawPhysicsDebugColor(eColor color, bool drawInstantly /*= false*/)
{
	if (Physics_Server::IsShowDebug == true)
	{
		//unsigned long long frameTickCount = MainTimer::GetCurrentFrameTime();

		//if (this->mLastRenderFrameTickCount != frameTickCount)
		//{
			Render(color, drawInstantly);
		//}

		//this->mLastRenderFrameTickCount = frameTickCount;
	}
}
