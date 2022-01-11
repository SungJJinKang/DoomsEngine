#include "Input/GraphicsAPIInput.h"


namespace dooms
{
	namespace input
	{
		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphisAPIInput(void* const platformWindow)
		{
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeInitializeGraphisAPIInput()
		{
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorMode(void* const platformWindow, const GraphicsAPIInput::eCursorMode cursorMode)
		{
		}

	}
}