#include "Graphics_Setting.h"
#include "Game/ConfigData.h"

void doom::graphics::Graphics_Setting::LoadData()
{
	const int width = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDTH");
	const int height = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");

	Graphics_Setting::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "MULTI_SAMPLE");
	Graphics_Setting::ScreenSize = { width, height };
	Graphics_Setting::ScreenRatio = static_cast<float>(width) / static_cast<float>(height);

	bmIsGraphicsSettingLoaded = true;
}

void doom::graphics::Graphics_Setting::SetWindow(GLFWwindow* const _window)
{
	Graphics_Setting::Window = _window;
}

