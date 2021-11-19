#include "Graphics_Setting.h"
#include "Game/ConfigData.h"

void dooms::graphics::Graphics_Setting::LoadData()
{
	const INT32 width = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "SCREEN_WIDTH");
	const INT32 height = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "SCREEN_HEIGHT");

	Graphics_Setting::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<INT32>("Graphics", "MULTI_SAMPLE");
	Graphics_Setting::ScreenSize[0] = width;
	Graphics_Setting::ScreenSize[1] = height;

	Graphics_Setting::ScreenRatio = static_cast<FLOAT32>(width) / static_cast<FLOAT32>(height);

}

void dooms::graphics::Graphics_Setting::SetWindow(GLFWwindow* const _window)
{
	Graphics_Setting::Window = _window;
}

