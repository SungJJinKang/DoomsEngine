#include "imguiHelper.h"

#include <imgui.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void dooms::ui::imguiHelper::InitializeImgui(GLFWwindow* const glfwWindow, const char* const glslVersion)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void dooms::ui::imguiHelper::ShutdownImgui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void dooms::ui::imguiHelper::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void dooms::ui::imguiHelper::Render()
{
    ImGui::Render();
}

void dooms::ui::imguiHelper::PostRender()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static bool show_demo_window = true;

void dooms::ui::imguiHelper::ShowDemoUpdate()
{

    ImGui::ShowDemoWindow(&show_demo_window);
}

// TODO : when input hover on imgui, disable dispatch imput to my application
