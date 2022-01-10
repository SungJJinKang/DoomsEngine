#include "GraphicsSetting.h"
#include "Game/ConfigData.h"

void dooms::graphics::graphicsSetting::LoadData()
{
	graphicsSetting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "DRAW_MASKED_OCCLUSION_CULLING_BIN_TRIANGLE_STAGE_DEBUGGER");
	graphicsSetting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "DRAW_MASKED_OCCLUSION_CULLING_TILE_COVERAGE_MASK_DEBUGGER");
	graphicsSetting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "DRAW_MASKED_OCCLUSION_CULLING_TILE_L0_MAX_DEPTH_VALUE_DEBUGGER");

}
