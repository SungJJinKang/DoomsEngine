#pragma once

#include <Core.h>

struct GLFWwindow;

namespace dooms
{
	namespace ui
	{
		namespace engineGUIServer
		{
			void Initialize(GLFWwindow* const glfwWindow, const char* const glslVersion);
			void ShutDown();

			void PreRender();
			void Render();
			void PostRender();

			inline extern bool IsEngineGUIVisible = true;
		};
	}
}

