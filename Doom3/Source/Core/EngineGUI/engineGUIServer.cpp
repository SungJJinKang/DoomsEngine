#include "EngineGUIServer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imguiHelper/imguiWithReflection.h"

#include "GUIModules/LogGUI.h"
#include "GUIModules/SceneGUI.h"


namespace dooms::ui::engineGUIServer
{
    static void InitializeGUIModules()
    {
        dooms::ui::log::Initialize();
    }

    static void RenderGUIModules()
    {
        dooms::ui::log::Render();
        dooms::ui::sceneGUI::Render();
    }
}


void dooms::ui::engineGUIServer::Initialize(GLFWwindow* const glfwWindow, const char* const glslVersion)
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

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

	dooms::ui::imguiWithReflection::Initialize();
    dooms::ui::engineGUIServer::InitializeGUIModules();
}

void dooms::ui::engineGUIServer::ShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void dooms::ui::engineGUIServer::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}



void dooms::ui::engineGUIServer::Render()
{
	dooms::ui::imguiWithReflection::UpdateGUI_DObjectsVisibleOnGUI();
    RenderGUIModules();
    ImGui::Render();
}

void dooms::ui::engineGUIServer::PostRender()
{
    dooms::ui::imguiWithReflection::ClearId();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


