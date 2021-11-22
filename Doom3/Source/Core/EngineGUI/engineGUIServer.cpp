#include "EngineGUIServer.h"

#include "imguiHelper/imguiHelper.h"
#include "imguiHelper/imguiWithReflection.h"

void dooms::ui::engineGUIServer::Initialize(GLFWwindow* const glfwWindow, const char* const glslVersion)
{
	dooms::ui::imguiHelper::InitializeImgui(glfwWindow, glslVersion);
}

void dooms::ui::engineGUIServer::ShutDown()
{
	dooms::ui::imguiHelper::ShutdownImgui();
}

void dooms::ui::engineGUIServer::PreRender()
{
	dooms::ui::imguiHelper::PreRender();
}

void dooms::ui::engineGUIServer::Render()
{
	dooms::ui::imguiWithReflection::UpdateGUI_DObjectsVisibleOnGUI();
	dooms::ui::imguiHelper::Render();
}

void dooms::ui::engineGUIServer::PostRender()
{
	dooms::ui::imguiHelper::PostRender();
}
