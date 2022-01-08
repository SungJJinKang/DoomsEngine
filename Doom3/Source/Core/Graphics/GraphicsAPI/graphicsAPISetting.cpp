#include "graphicsAPISetting.h"
#include "Game/ConfigData.h"

void dooms::graphics::graphicsAPISetting::LoadData()
{
	const INT32 width = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "SCREEN_WIDTH");
	const INT32 height = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "SCREEN_HEIGHT");

	graphicsAPISetting::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "MULTI_SAMPLE");
	graphicsAPISetting::ScreenSize[0] = width;
	graphicsAPISetting::ScreenSize[1] = height;

	graphicsAPISetting::ScreenRatio = static_cast<FLOAT32>(width) / static_cast<FLOAT32>(height);

}

