#include "RenderPhysics.h"
#include "Physics_Server.h"
#include "../Graphics/DebugGraphics.h"

void doom::physics::RenderPhysics::DrawPhysicsDebug()
{
	if (Physics_Server::IsShowDebug == true && graphics::DebugGraphics::mbDrawDebug == true)
	{
		Render(graphics::DebugGraphics::mDefaultDebugColor);
	}
}
