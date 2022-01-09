#pragma once

namespace dooms
{
	namespace ui
	{
		namespace engineGUIServer
		{
			extern void Initialize();
			extern void ShutDown();

			extern void PreRender();
			extern void Render();
			extern void PostRender();

			extern bool GetIsEngineGUIAvaliable();

			inline extern bool IsEngineGUIVisible = true;

			
		};
	}
}

