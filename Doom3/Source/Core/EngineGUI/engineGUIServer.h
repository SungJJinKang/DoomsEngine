#pragma once

struct GLFWwindow;

namespace dooms
{
	namespace ui
	{
		namespace engineGUIServer
		{
			extern void Initialize(GLFWwindow* const glfwWindow, const char* const glslVersion);
			extern void ShutDown();

			extern void PreRender();
			extern void Render();
			extern void PostRender();

			extern bool GetIsEngineGUIAvaliable();

			inline extern bool IsEngineGUIVisible = true;

			
		};
	}
}

