#include "graphicsAPISetting.h"
#include "EngineConfigurationData/ConfigData.h"

int dooms::graphics::graphicsAPISetting::ScreenSize[2] = {0, 0};
float dooms::graphics::graphicsAPISetting::ScreenRatio{0.0f};
unsigned int dooms::graphics::graphicsAPISetting::MultiSamplingNum{0};
bool dooms::graphics::graphicsAPISetting::DefaultIsAlphaTestOn{true};
bool dooms::graphics::graphicsAPISetting::DefaultIsBlendOn{false};
dooms::graphics::eDepthPrePassType dooms::graphics::graphicsAPISetting::DepthPrePassType{ dooms::graphics::eDepthPrePassType::Disable };
dooms::graphics::GraphicsAPI::eBlendFactor dooms::graphics::graphicsAPISetting::DefaultBlendSourceFactor{ GraphicsAPI::eBlendFactor::SRC_COLOR };
dooms::graphics::GraphicsAPI::eBlendFactor dooms::graphics::graphicsAPISetting::DefaultBlendDestinationFactor{ GraphicsAPI::eBlendFactor::ZERO };

void dooms::graphics::graphicsAPISetting::LoadData()
{
	const INT32 width = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "SCREEN_WIDTH");
	const INT32 height = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "SCREEN_HEIGHT");

	graphicsAPISetting::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "MULTI_SAMPLE");
	graphicsAPISetting::ScreenSize[0] = width;
	graphicsAPISetting::ScreenSize[1] = height;

	graphicsAPISetting::ScreenRatio = static_cast<FLOAT32>(width) / static_cast<FLOAT32>(height);

}

