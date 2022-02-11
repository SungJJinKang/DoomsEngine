#include "Graphics_Server.h"

#include "../Game/GameCore.h"
#include "GraphicsAPI/Manager/GraphicsAPIManager.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "graphicsSetting.h"
#include "GraphicsAPI/graphicsAPISetting.h"

bool dooms::graphics::Graphics_Server::InitializeGraphicsAPI(GraphicsAPI::eGraphicsAPIType graphicsAPIType)
{
	dooms::graphics::graphicsSetting::LoadData();
	dooms::graphics::graphicsAPISetting::LoadData();

	bool isSuccess = false;

	if(graphicsAPIType == GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE)
	{
		dooms::ui::PrintText("Read Target Graphics API from Config.ini file");

		const std::string targetGraphicsAPI = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("Graphics", "GRAPHICS_API");
		if (targetGraphicsAPI == "OPENGL")
		{
			graphicsAPIType = GraphicsAPI::eGraphicsAPIType::OpenGL;
		}
		else if (targetGraphicsAPI == "DX11_10" || targetGraphicsAPI == "DX11")
		{
			graphicsAPIType = GraphicsAPI::eGraphicsAPIType::DX11_10;
		}
		else
		{
			D_ASSERT(false);
		}
	}
	

	switch (graphicsAPIType)
	{
	case GraphicsAPI::eGraphicsAPIType::OpenGL:
		isSuccess = GraphicsAPIManager::Initialize(GraphicsAPI::eGraphicsAPIType::OpenGL);
		break;
	case GraphicsAPI::eGraphicsAPIType::DX11_10: 
		isSuccess = GraphicsAPIManager::Initialize(GraphicsAPI::eGraphicsAPIType::DX11_10);
		break;
	default:
		dooms::ui::PrintText("Graphics API isn't chosen. Default Graphics API OPENGL is chosen.");
		isSuccess = GraphicsAPIManager::Initialize(GraphicsAPI::eGraphicsAPIType::OpenGL); // If any specific api type isn't passed, just use opengl....
		D_ASSERT(false);
	}

	D_ASSERT(isSuccess == true);

	return isSuccess;
}

void dooms::graphics::Graphics_Server::Init(const int argc, char* const* const argv)
{
	dooms::ui::engineGUIServer::Initialize();

	mGraphicsPipeLine.Initialize();

	return;
}

void dooms::graphics::Graphics_Server::LateInit()
{
	mGraphicsPipeLine.LateInitialize();
}


void dooms::graphics::Graphics_Server::PreRenders()
{
	D_START_PROFILING(mGraphicsPipeLine_PreRender, dooms::profiler::eProfileLayers::Rendering);
	mGraphicsPipeLine.PreRender();
	D_END_PROFILING(mGraphicsPipeLine_PreRender);

}

void dooms::graphics::Graphics_Server::Renders()
{
	D_START_PROFILING(RENDER, dooms::profiler::eProfileLayers::Rendering);
	mGraphicsPipeLine.Render();
	D_END_PROFILING(RENDER);


}

void dooms::graphics::Graphics_Server::PostRenders()
{
	D_START_PROFILING(PostRender, dooms::profiler::eProfileLayers::Rendering);
	mGraphicsPipeLine.PostRender();
	D_END_PROFILING(PostRender);
}

void dooms::graphics::Graphics_Server::Update()
{
	PreRenders();

	Renders();

	PostRenders();
}

void dooms::graphics::Graphics_Server::OnEndOfFrame()
{
	graphics::GraphicsAPI::SwapBuffer();
}


dooms::graphics::Graphics_Server::Graphics_Server()
	: mGraphicsPipeLine{*this}, mUniformBufferObjectManager(), mLightManager(), mPIPManager()
{

}

dooms::graphics::Graphics_Server::~Graphics_Server()
{
	dooms::ui::engineGUIServer::ShutDown();
}

