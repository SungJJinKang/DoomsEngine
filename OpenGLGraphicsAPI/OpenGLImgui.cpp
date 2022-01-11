#include "PlatformImgui/PlatformImgui.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "GraphicsAPI.h"


bool dooms::graphics::PlatformImgui::Initialize(ImGuiContext* const imGuiContext, ImGuiMemAllocFunc p_alloc_func, ImGuiMemFreeFunc p_free_func, void* p_user_data)
{
    assert(imGuiContext != nullptr);

    ImGui::SetCurrentContext(imGuiContext);
    ImGui::SetAllocatorFunctions(p_alloc_func, p_free_func, p_user_data);

    GLFWwindow* const glfwWindow = reinterpret_cast<GLFWwindow*>(GraphicsAPI::GetPlatformWindow());
    assert(glfwWindow != nullptr);

    bool isSuccess = true;

    isSuccess &= ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    const std::string openglVersion = GraphicsAPI::GetPlatformVersion();
    isSuccess &= ImGui_ImplOpenGL3_Init(openglVersion.c_str());

    return isSuccess;
}

bool dooms::graphics::PlatformImgui::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    return true;
}

void dooms::graphics::PlatformImgui::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void dooms::graphics::PlatformImgui::PostRender()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
