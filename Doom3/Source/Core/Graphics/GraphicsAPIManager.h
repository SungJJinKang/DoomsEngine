#pragma once

#include "GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		namespace GraphicsAPIManager
		{
			void Initialize();
			void DEBUG_CALLBACK(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);
			void SwapBuffer();
			void SetWindowTitle(const char* const title);
		};
	}
}

