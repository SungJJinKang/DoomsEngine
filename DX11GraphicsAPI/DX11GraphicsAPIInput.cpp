#include "Input/GraphicsAPIInput.h"


namespace dooms
{
	namespace input
	{
		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphisAPIInput()
		{
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeInitializeGraphisAPIInput()
		{
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorMode(const GraphicsAPIInput::eCursorMode cursorMode)
		{
		}

	}
}