#include "PlatformImgui/PlatformImgui.h"

#include <cassert>

#include "GLFW/glfw3.h"

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


namespace dooms
{
	namespace imgui
	{
		DOOMS_ENGINE_GRAPHICS_API bool InitializePlatformImgui(void* platformWindow, const char* apiVersion, ImGuiContext* const imGuiContext, ImGuiMemAllocFunc p_alloc_func, ImGuiMemFreeFunc p_free_func, void* p_user_data)
		{
			assert(imGuiContext != nullptr);

			ImGui::SetCurrentContext(imGuiContext);
			ImGui::SetAllocatorFunctions(p_alloc_func, p_free_func, p_user_data);

			GLFWwindow* const glfwWindow = reinterpret_cast<GLFWwindow*>(platformWindow);
			assert(glfwWindow != nullptr);

			bool isSuccess = true;

			isSuccess &= ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
			isSuccess &= ImGui_ImplOpenGL3_Init(apiVersion);

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