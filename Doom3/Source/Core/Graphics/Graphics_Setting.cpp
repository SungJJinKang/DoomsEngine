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
	Graphics_Setting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "DRAW_MASKED_OCCLUSION_CULLING_BIN_TRIANGLE_STAGE_DEBUGGER");
	Graphics_Setting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "DRAW_MASKED_OCCLUSION_CULLING_TILE_COVERAGE_MASK_DEBUGGER");
	Graphics_Setting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "DRAW_MASKED_OCCLUSION_CULLING_TILE_L0_MAX_DEPTH_VALUE_DEBUGGER");

}

void dooms::graphics::Graphics_Setting::SetWindow(GLFWwindow* const _window)
{
	Graphics_Setting::Window = _window;
}

