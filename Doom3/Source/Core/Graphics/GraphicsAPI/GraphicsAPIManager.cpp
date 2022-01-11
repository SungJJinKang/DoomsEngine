#include "GraphicsAPIManager.h"

#include <Windows.h>

#include "graphicsAPISetting.h"
#include "Input/GraphicsAPIInput.h"
#include <EngineGUI/PrintText.h>

void dooms::graphics::GraphicsAPIManager::LoadGraphicsAPI(const eGraphicsAPIType graphicsAPIType)
{
	HMODULE hModule = reinterpret_cast<HMODULE>(mGraphicsAPILoader.LoadGraphicsAPILibrary(graphicsAPIType));
	D_ASSERT(hModule != NULL);
	if(hModule != NULL)
	{
		mGraphicsAPIType = graphicsAPIType;
	}
}

void dooms::graphics::GraphicsAPIManager::SetDefaultSettingOfAPI()
{
	input::GraphicsAPIInput::SetCursorMode(input::GraphicsAPIInput::eCursorMode::CURSOR_MODE_NORMAL);
	graphics::GraphicsAPI::SetIsDepthTestEnabled(true);
	graphics::GraphicsAPI::SetDepthFunc(GraphicsAPI::LESS);
	//graphics::GraphicsAPI::SetIsAlphaTestEnabled(dooms::graphics::graphicsAPISetting::DefaultIsAlphaTestOn);
	graphics::GraphicsAPI::SetIsBlendEnabled(dooms::graphics::graphicsAPISetting::DefaultIsBlendOn);
	graphics::GraphicsAPI::SetBlendFactor(dooms::graphics::graphicsAPISetting::DefaultBlendSourceFactor, dooms::graphics::graphicsAPISetting::DefaultBlendDestinationFactor);
	graphics::GraphicsAPI::SetCullFace(GraphicsAPI::CULLFACE_BACK);
	graphics::GraphicsAPI::SetFrontFaceWinding(GraphicsAPI::CCW);
	graphics::GraphicsAPI::SetVSync(false);
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

dooms::graphics::GraphicsAPIManager::GraphicsAPIManager() = default;
dooms::graphics::GraphicsAPIManager::~GraphicsAPIManager() = default;
dooms::graphics::GraphicsAPIManager::GraphicsAPIManager(GraphicsAPIManager&&) noexcept = default;
dooms::graphics::GraphicsAPIManager& dooms::graphics::GraphicsAPIManager::operator=(GraphicsAPIManager&&) noexcept = default;

bool dooms::graphics::GraphicsAPIManager::Initialize(const eGraphicsAPIType graphicsAPIType)
{
	LoadGraphicsAPI(graphicsAPIType);
	GraphicsAPI::SetDebugFunction(dooms::graphics::GraphicsAPIManager::GraphisAPIDebugCallBack);

	unsigned int isSuccess = 0;
	{
		isSuccess |= GraphicsAPI::Initialize(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight(), graphicsAPISetting::GetMultiSamplingNum());
		D_ASSERT(isSuccess == 0);
		if (isSuccess != 0)
		{
			dooms::ui::PrintText("Fail to GraphicsAPI::Initialize ( Error Code : %u )", isSuccess);
		}
	}
	SetDefaultSettingOfAPI();
	isSuccess |= input::GraphicsAPIInput::Initialize();
	D_ASSERT(isSuccess == 0);

	return isSuccess == 0;
}

bool dooms::graphics::GraphicsAPIManager::DeInitialize()
{
	unsigned int isSuccess = 0;

	isSuccess |= graphics::GraphicsAPI::DeInitialize();
	D_ASSERT(isSuccess == 0);
	isSuccess |= input::GraphicsAPIInput::DeInitialize();
	D_ASSERT(isSuccess == 0);
	isSuccess |= mGraphicsAPILoader.UnLoadGraphicsAPILibrary();
	D_ASSERT(isSuccess == 0);

	return isSuccess == 0;
}

dooms::graphics::eGraphicsAPIType dooms::graphics::GraphicsAPIManager::GetGraphicsAPIType() const
{
	return mGraphicsAPIType;
}
