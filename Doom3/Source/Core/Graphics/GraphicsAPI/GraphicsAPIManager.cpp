#include "GraphicsAPIManager.h"

#include "graphicsAPISetting.h"
#include "Input/GraphicsAPIInput.h"

void dooms::graphics::GraphicsAPIManager::LoadGraphicsAPI(const eGraphicsAPIType graphicsAPIType)
{
	
	mGraphicsAPILoader.LoadGraphicsAPILibrary(graphicsAPIType);
}

void dooms::graphics::GraphicsAPIManager::SetDefaultSettingOfAPI()
{
	graphics::GraphicsAPIInput::SetCursorMode(graphics::GraphicsAPIInput::eCursorMode::CURSOR_MODE_NORMAL);
	graphics::GraphicsAPI::EnableDepthTest(true);
	graphics::GraphicsAPI::DepthFunc(GraphicsAPI::LESS);
	graphics::GraphicsAPI::EnableAlphaTest(dooms::graphics::graphicsAPISetting::DefaultIsAlphaTestOn);
	graphics::GraphicsAPI::EnableBlend(dooms::graphics::graphicsAPISetting::DefaultIsBlendOn);
	graphics::GraphicsAPI::SetBlendFactor(GraphicsAPI::eBlendFactor::SRC_ALPHA, GraphicsAPI::eBlendFactor::ONE_MINUS_SRC_ALPHA);
	graphics::GraphicsAPI::SetCullFace(GraphicsAPI::CULLFACE_BACK);
	graphics::GraphicsAPI::SetFrontFaceWinding(GraphicsAPI::CCW);
	graphics::GraphicsAPI::SetVSync(false);
}

dooms::graphics::GraphicsAPIManager::GraphicsAPIManager() = default;
dooms::graphics::GraphicsAPIManager::~GraphicsAPIManager() = default;
dooms::graphics::GraphicsAPIManager::GraphicsAPIManager(GraphicsAPIManager&&) noexcept = default;
dooms::graphics::GraphicsAPIManager& dooms::graphics::GraphicsAPIManager::operator=(GraphicsAPIManager&&) noexcept = default;

void dooms::graphics::GraphicsAPIManager::Initialize(const eGraphicsAPIType graphicsAPIType)
{
	GraphicsAPI::Initialize();


}

void dooms::graphics::GraphicsAPIManager::DeInitialize()
{
	graphics::GraphicsAPI::DeInitialize();
	mGraphicsAPILoader.UnLoadGraphicsAPILibrary();
}
