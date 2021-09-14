#pragma once

#include "Graphics_Core.h"

namespace doom
{
	namespace graphics
	{
		struct GraphicsAPIManager
		{
			static void Initialize();

			static void DEBUG_CALLBACK(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);

			static void SwapBuffer();
		};
	}
}

