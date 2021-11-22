#pragma once

struct GLFWwindow;

namespace dooms
{
	namespace ui
	{
		namespace imguiHelper
		{
			void InitializeImgui(GLFWwindow* const glfwWindow, const char* const glslVersion);
			void ShutdownImgui();
			void PreRender();
			void Render();
			void PostRender();
			void ShowDemoUpdate();
		};
	}
}


