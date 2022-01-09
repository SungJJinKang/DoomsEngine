#include "PlatformImgui/PlatformImgui.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "GraphicsAPI.h"

void dooms::graphics::PlatformImgui::Initialize()
{
    ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(GraphicsAPI::GetPlatformWindow()), true);
    const std::string openglVersion = GraphicsAPI::GetPlatformVersion();
    ImGui_ImplOpenGL3_Init(openglVersion.c_str());
}

void dooms::graphics::PlatformImgui::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

void dooms::graphics::PlatformImgui::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void dooms::graphics::PlatformImgui::Render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
