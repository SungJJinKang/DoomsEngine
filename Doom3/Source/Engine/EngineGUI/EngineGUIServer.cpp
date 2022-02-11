#include "EngineGUIServer.h"

#include <Graphics/GraphicsAPI/PlatformImgui/PlatformImgui.h>

#include "imguiHelper/imguiWithReflection.h"

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "engineGUIServerHelper.h"
#include "GUIModules/EngineGUIModule.h"

bool dooms::ui::EngineGUIServer::DestroyImgui()
{
    const bool isSuccess = dooms::graphics::PlatformImgui::ShutDownPlatformImgui();
    D_ASSERT(isSuccess == true);
    ImGui::DestroyContext();

    return isSuccess;
}

void dooms::ui::EngineGUIServer::PreRender()
{
    if (bmIsEngineGUIAvaliable == true)
    {
        graphics::PlatformImgui::PreRenderPlatformImgui();
        ImGui::NewFrame();
    }
}



void dooms::ui::EngineGUIServer::Render()
{
    if (bmIsEngineGUIAvaliable == true)
    {
        dooms::ui::imguiWithReflection::UpdateGUI_DObjectsVisibleOnGUI();
     
        for(EngineGUIModule* module : mEngineGUIModules)
        {
            D_ASSERT(IsValid(module));
            if(IsValid(module))
            {
                module->Render();
            }
        }

        ImGui::Render();
    }
}

void dooms::ui::EngineGUIServer::PostRender()
{
    if(bmIsEngineGUIAvaliable == true)
    {
        bmIsEngineGUIAvaliable = true;

        dooms::ui::imguiWithReflection::ClearId();
        dooms::graphics::PlatformImgui::PostRenderPlatformImgui();
    }
}

bool dooms::ui::EngineGUIServer::GetIsEngineGUIAvaliable() const
{
    return bmIsEngineGUIAvaliable;
}

bool& dooms::ui::EngineGUIServer::GetIsEngineGUIAvaliableRef()
{
    return bmIsEngineGUIAvaliable;
}


bool dooms::ui::EngineGUIServer::InitializeImgui()
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
	isSuccess &= static_cast<bool>(dooms::graphics::PlatformImgui::InitializePlatformImgui(dooms::graphics::GraphicsAPI::GetPlatformWindow(), dooms::graphics::GraphicsAPI::GetPlatformVersion(), imGuiContext, *p_alloc_func, *p_free_func, &p_user_data));

    return isSuccess;
}

dooms::ui::EngineGUIServer::EngineGUIServer()
	: bmIsEngineGUIAvaliable(true)
{
}

dooms::ui::EngineGUIServer::~EngineGUIServer()
{
    DestroyImgui();
}

void dooms::ui::EngineGUIServer::InitializeEngineGUIModules()
{
	mEngineGUIModules = engineGUIServerHelper::CreateDefaultEngineGUIModules();
	for (EngineGUIModule* module : mEngineGUIModules)
	{
		module->Init();
	}
}

void dooms::ui::EngineGUIServer::Init(const int argc, char* const* const argv)
{
	bool isSuccess = InitializeImgui();
    dooms::ui::imguiWithReflection::Initialize();

    InitializeEngineGUIModules();

    D_ASSERT(isSuccess == true);
}

void dooms::ui::EngineGUIServer::Update()
{
}

void dooms::ui::EngineGUIServer::OnEndOfFrame()
{
}
