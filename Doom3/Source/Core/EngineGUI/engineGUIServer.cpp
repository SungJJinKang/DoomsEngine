#include "engineGUIServer.h"

#include <Graphics/GraphicsAPI/PlatformImgui/PlatformImgui.h>

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
        dooms::ui::maskedOcclusionCulliingDebugger::Render();
        dooms::ui::drawCallCounterGUI::Render();
    }
}


bool dooms::ui::engineGUIServer::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGuiContext* const imGuiContext = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    bool isSuccess = (imGuiContext != nullptr);

    // TODO : Block dispatch imput to application when mouse hover on gui
    io.WantCaptureMouse = true;
    io.WantCaptureKeyboard = true;


    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    ImGuiMemAllocFunc p_alloc_func;
    ImGuiMemFreeFunc p_free_func;
    void* p_user_data;
    ImGui::GetAllocatorFunctions(&p_alloc_func, &p_free_func, &p_user_data);
    isSuccess &= dooms::graphics::PlatformImgui::Initialize(imGuiContext, *p_alloc_func, *p_free_func, &p_user_data);

    //ImGui::SetCurrentContext()
	dooms::ui::imguiWithReflection::Initialize();
    dooms::ui::engineGUIServer::InitializeGUIModules();

    return isSuccess;
}

bool dooms::ui::engineGUIServer::ShutDown()
{
    const bool isSuccess = dooms::graphics::PlatformImgui::ShutDown();
    D_ASSERT(isSuccess == true);
    ImGui::DestroyContext();

    return isSuccess;
}

void dooms::ui::engineGUIServer::PreRender()
{
    if (IsEngineGUIVisible == true)
    {
        graphics::PlatformImgui::PreRender();
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
        dooms::graphics::PlatformImgui::PostRender();
    }
}

bool dooms::ui::engineGUIServer::GetIsEngineGUIAvaliable()
{
    return IsEngineGUIAvaliable;
}


