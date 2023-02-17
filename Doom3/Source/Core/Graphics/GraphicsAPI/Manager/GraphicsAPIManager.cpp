#include "GraphicsAPIManager.h"

#include <shellscalingapi.h>
#include <Windows.h>

#include "../graphicsAPISetting.h"
#include "../Input/GraphicsAPIInput.h"
#include "EngineConfigurationData/ConfigData.h"
#include <EngineGUI/PrintText.h>

std::unique_ptr<dooms::graphics::GraphicsAPILoader> dooms::graphics::GraphicsAPIManager::_GraphicsAPILoader{};
void dooms::graphics::GraphicsAPIManager::LoadGraphicsAPI(const GraphicsAPI::eGraphicsAPIType graphicsAPIType)
{
	if(_GraphicsAPILoader == nullptr)
	{
		_GraphicsAPILoader = std::make_unique<dooms::graphics::GraphicsAPILoader>();
	}

	HMODULE hModule = reinterpret_cast<HMODULE>(_GraphicsAPILoader->LoadGraphicsAPILibrary(graphicsAPIType));
	D_ASSERT(hModule != NULL);
}

void dooms::graphics::GraphicsAPIManager::SetDefaultSettingOfAPI()
{
	input::GraphicsAPIInput::SetCursorMode(dooms::graphics::GraphicsAPI::GetPlatformWindow(), input::GraphicsAPIInput::eCursorMode::SHOW_CURSOR_UNLOCK_CURSOR_FROM_WINDOW);
	graphics::GraphicsAPI::SetIsDepthTestEnabled(true);
	graphics::GraphicsAPI::SetIsStencilTestEnabled(false);
	graphics::GraphicsAPI::SetDepthFunc(GraphicsAPI::LESS);
	graphics::GraphicsAPI::SetIsAlphaTestEnabled(dooms::graphics::graphicsAPISetting::DefaultIsAlphaTestOn);
	graphics::GraphicsAPI::SetIsBlendEnabled(dooms::graphics::graphicsAPISetting::DefaultIsBlendOn);
	graphics::GraphicsAPI::SetBlendFactor(dooms::graphics::graphicsAPISetting::DefaultBlendSourceFactor, dooms::graphics::graphicsAPISetting::DefaultBlendDestinationFactor);
	graphics::GraphicsAPI::SetCullFace(GraphicsAPI::CULLFACE_BACK);

	if(graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		graphics::GraphicsAPI::SetFrontFaceWinding(GraphicsAPI::CCW);
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		graphics::GraphicsAPI::SetFrontFaceWinding(GraphicsAPI::CCW);
	}
	else
	{
		ASSUME_ZERO;
	}

	graphics::GraphicsAPI::SetVSync(false);
	graphics::GraphicsAPI::SetViewport(0, 0, 0, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());

	std::string windowTitle = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("Graphics", "WINDOW_TITLE");

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		windowTitle += " - OpenGL";
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		windowTitle += " - D3D11";
	}
	else
	{
		ASSUME_ZERO;
	}

	graphics::GraphicsAPI::SetWindowTitle(windowTitle.c_str());
}

void dooms::graphics::GraphicsAPIManager::GraphisAPIDebugCallBack(const char* const debugMessage, const graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity severity)
{
	D_ASSERT_LOG
	(
		severity != graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::HIGH &&
		severity != graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::MEDIUM, 
		"Graphis API Callback : %s", debugMessage
	);

	if
	(
		severity == graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::HIGH ||
		severity == graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::MEDIUM
	)
	{
		D_DEBUG_LOG(eLogType::D_LOG_TYPE5, "Graphis API Callback : %s", debugMessage);
	}
}
 

bool dooms::graphics::GraphicsAPIManager::Initialize(const GraphicsAPI::eGraphicsAPIType graphicsAPIType)
{
	if(graphicsAPIType != GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE)
	{
		LoadGraphicsAPI(graphicsAPIType);
		if (GraphicsAPI::SetDebugFunction != nullptr)
		{
			GraphicsAPI::SetDebugFunction(dooms::graphics::GraphicsAPIManager::GraphisAPIDebugCallBack);
		}

		switch (graphicsAPIType)
		{
		case GraphicsAPI::eGraphicsAPIType::OpenGL:
			dooms::ui::PrintText("Initilize OPENGL");
			break;
		case GraphicsAPI::eGraphicsAPIType::DX11_10:
			dooms::ui::PrintText("Initilize DIRECTX 11");
			break;
		default:
			D_ASSERT(false);
			return false;
		}

		SetProcessDpiAwareness(PROCESS_DPI_AWARENESS::PROCESS_SYSTEM_DPI_AWARE);

		unsigned int result = 1;
		result &= GraphicsAPI::InitializeGraphicsAPI(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight(), graphicsAPISetting::GetMultiSamplingNum());
		D_ASSERT_LOG(result == 1, "Fail to GraphicsAPI::InitializeGraphisAPIInput ( Error Code : %u )", result);

		SetDefaultSettingOfAPI();
		result &= input::GraphicsAPIInput::InitializeGraphisAPIInput(dooms::graphics::GraphicsAPI::GetPlatformWindow());
		D_ASSERT(result == 1);

		return result == 1;
	}
	else
	{
		return false;
	}
}

bool dooms::graphics::GraphicsAPIManager::DeInitialize()
{
	unsigned int result = 1;

	result &= graphics::GraphicsAPI::DeinitializeGraphicsAPI();
	D_ASSERT(result == 1);
	result &= input::GraphicsAPIInput::DeInitializeGraphisAPIInput();
	D_ASSERT(result == 1);
	D_ASSERT(_GraphicsAPILoader != nullptr);
	result &= static_cast<unsigned int>(_GraphicsAPILoader->UnLoadGraphicsAPILibrary());
	D_ASSERT(result == 1);

	_GraphicsAPILoader.reset();

	return result == 1;
}
