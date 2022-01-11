#include "PlatformImgui/PlatformImgui.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "GraphicsAPI.h"

namespace dooms
{
	namespace input
	{
		DOOMS_ENGINE_GRAPHICS_API bool InitializePlatformImgui(ImGuiContext* const imGuiContext, ImGuiMemAllocFunc p_alloc_func, ImGuiMemFreeFunc p_free_func, void* p_user_data)
		{
			assert(imGuiContext != nullptr);

			ImGui::SetCurrentContext(imGuiContext);
			ImGui::SetAllocatorFunctions(p_alloc_func, p_free_func, p_user_data);

			GLFWwindow* const glfwWindow = reinterpret_cast<GLFWwindow*>(graphics::GraphicsAPI::GetPlatformWindow());
			assert(glfwWindow != nullptr);

			bool isSuccess = true;

			isSuccess &= ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
			const char* const openglVersion = graphics::GraphicsAPI::GetPlatformVersion();
			isSuccess &= ImGui_ImplOpenGL3_Init(openglVersion);

			return isSuccess;
		}

		DOOMS_ENGINE_GRAPHICS_API bool ShutDownPlatformImgui()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();

			return true;
		}

		DOOMS_ENGINE_GRAPHICS_API void PreRenderPlatformImgui()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
		}

		DOOMS_ENGINE_GRAPHICS_API void PostRenderPlatformImgui()
		{
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

	}
}