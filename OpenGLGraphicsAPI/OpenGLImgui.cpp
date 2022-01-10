#include "PlatformImgui/PlatformImgui.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "GraphicsAPI.h"

void dooms::graphics::PlatformImgui::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // TODO : Block dispatch imput to application when mouse hover on gui
    io.WantCaptureMouse = true;
    io.WantCaptureKeyboard = true;


    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(GraphicsAPI::GetPlatformWindow()), true);
    const std::string openglVersion = GraphicsAPI::GetPlatformVersion();
    ImGui_ImplOpenGL3_Init(openglVersion.c_str());
}

void dooms::graphics::PlatformImgui::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void dooms::graphics::PlatformImgui::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void dooms::graphics::PlatformImgui::Render()
{
    ImGui::Render();
}

void dooms::graphics::PlatformImgui::PostRender()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
