#include "EngineGUIServer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imguiHelper/imguiWithReflection.h"

#include "GUIModules/LogGUI.h"
#include "GUIModules/SceneGUI.h"
#include "GUIModules/ProfilerGUI.h"
#include "GUIModules/ThreadProfilerGUI.h"
#include "GUIModules/MaskedOcclusionCulliingDebugger.h"
#include "GUIModules/drawCallCounterGUI.h"


namespace dooms::ui::engineGUIServer
{
    static void InitializeGUIModules()
    {
        dooms::ui::log::Initialize();
        dooms::ui::threadProfilerGUI::Init();
    }

    static void RenderGUIModules()
    {
        dooms::ui::log::Render();
        dooms::ui::sceneGUI::Render();
        dooms::ui::profilerGUI::Render();
        dooms::ui::threadProfilerGUI::Render();
        //dooms::ui::maskedOcclusionCulliingDebugger::Render();
        dooms::ui::drawCallCounterGUI::Render();
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
    if (IsEngineGUIVisible == true)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
}



void dooms::ui::engineGUIServer::Render()
{
    if (IsEngineGUIVisible == true)
    {
        dooms::ui::imguiWithReflection::UpdateGUI_DObjectsVisibleOnGUI();
        RenderGUIModules();
        ImGui::Render();
    }
}

namespace dooms::ui::engineGUIServer
{
    static bool IsEngineGUIAvaliable = false;
}

void dooms::ui::engineGUIServer::PostRender()
{
    if(IsEngineGUIVisible == true)
    {
        IsEngineGUIAvaliable = true;

        dooms::ui::imguiWithReflection::ClearId();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

bool dooms::ui::engineGUIServer::GetIsEngineGUIAvaliable()
{
    return IsEngineGUIAvaliable;
}


