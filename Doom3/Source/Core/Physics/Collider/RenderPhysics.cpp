#include "RenderPhysics.h"
#include "Physics_Server.h"
#include "../Graphics/DebugGraphics.h"
#include <MainTimer.h>


#ifdef DEBUG_MODE

void doom::physics::RenderPhysics::DrawPhysicsDebugColor(eColor color, bool drawInstantly /*= false*/)
{
	if (Physics_Server::IsShowDebug == true)
	{
		//unsigned long long frameTickCount = MainTimer::GetCurrentTickCount();

		//if (this->mLastRenderFrameTickCount != frameTickCount)
		//{
		//color = eColor::Red;
			Render(color, drawInstantly);
		//}

		//this->mLastRenderFrameTickCount = frameTickCount;
	}
}

#endif