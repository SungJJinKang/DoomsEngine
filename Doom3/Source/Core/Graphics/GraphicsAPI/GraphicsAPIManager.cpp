#include "GraphicsAPIManager.h"

#include "graphicsAPISetting.h"
#include "Input/GraphicsAPIInput.h"
#include <EngineGUI/PrintText.h>

void dooms::graphics::GraphicsAPIManager::LoadGraphicsAPI(const eGraphicsAPIType graphicsAPIType)
{
	
	mGraphicsAPILoader.LoadGraphicsAPILibrary(graphicsAPIType);
}

void dooms::graphics::GraphicsAPIManager::SetDefaultSettingOfAPI()
{
	graphics::GraphicsAPIInput::SetCursorMode(graphics::GraphicsAPIInput::eCursorMode::CURSOR_MODE_NORMAL);
	graphics::GraphicsAPI::SetIsDepthTestEnabled(true);
	graphics::GraphicsAPI::SetDepthFunc(GraphicsAPI::LESS);
	graphics::GraphicsAPI::SetIsAlphaTestEnabled(dooms::graphics::graphicsAPISetting::DefaultIsAlphaTestOn);
	graphics::GraphicsAPI::SetIsBlendEnabled(dooms::graphics::graphicsAPISetting::DefaultIsBlendOn);
	graphics::GraphicsAPI::SetBlendFactor(dooms::graphics::graphicsAPISetting::DefaultBlendSourceFactor, dooms::graphics::graphicsAPISetting::DefaultBlendDestinationFactor);
	graphics::GraphicsAPI::SetCullFace(GraphicsAPI::CULLFACE_BACK);
	graphics::GraphicsAPI::SetFrontFaceWinding(GraphicsAPI::CCW);
	graphics::GraphicsAPI::SetVSync(false);
}

void dooms::graphics::GraphicsAPIManager::GraphisAPIDebugCallBack(const char* const debugMessage)
{
	//D_ASSERT_LOG(false, "Graphis API Callback : %s", debugMessage);
	dooms::ui::PrintText("Graphis API Callback : %s", debugMessage);
}

dooms::graphics::GraphicsAPIManager::GraphicsAPIManager() = default;
dooms::graphics::GraphicsAPIManager::~GraphicsAPIManager() = default;
dooms::graphics::GraphicsAPIManager::GraphicsAPIManager(GraphicsAPIManager&&) noexcept = default;
dooms::graphics::GraphicsAPIManager& dooms::graphics::GraphicsAPIManager::operator=(GraphicsAPIManager&&) noexcept = default;

void dooms::graphics::GraphicsAPIManager::Initialize(const eGraphicsAPIType graphicsAPIType)
{
	LoadGraphicsAPI(graphicsAPIType);
	GraphicsAPI::mDEBUG_FUNCTION = dooms::graphics::GraphicsAPIManager::GraphisAPIDebugCallBack;
	const unsigned int isSuccess = GraphicsAPI::Initialize(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight(), graphicsAPISetting::GetMultiSamplingNum());
	D_ASSERT(isSuccess == 0);
	if(isSuccess != 0)
	{
		dooms::ui::PrintText("Fail to GraphicsAPI::Initialize ( Error Code : %u )", isSuccess);
	}

}

void dooms::graphics::GraphicsAPIManager::DeInitialize()
{
	graphics::GraphicsAPI::DeInitialize();
	mGraphicsAPILoader.UnLoadGraphicsAPILibrary();
}
