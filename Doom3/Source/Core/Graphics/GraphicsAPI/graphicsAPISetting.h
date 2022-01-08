#pragma once

namespace dooms
{
	namespace graphics
	{
		namespace graphicsAPISetting
		{
			extern inline int ScreenSize[2] { 0, 0 };
			/// <summary>
			/// ScreenSize Width / ScreenSize Height
			/// </summary>
			extern inline float ScreenRatio{0.0f};
			extern inline unsigned int MultiSamplingNum{0};
			
			extern inline bool IsSortObjectFrontToBack{ true };

			extern inline bool IsDrawDebuggersEnabled{ true };

			extern inline bool IsDrawMaskedOcclusionCullingBinTriangleStageDebugger{ false };
			extern inline bool IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger{ false };
			extern inline bool IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger{ false };

			extern inline bool IsOverDrawVisualizationEnabled{ false };

			extern inline bool DrawRenderingBoundingBox{ false };
			extern inline float DefaultClearColor[4] { 0.0f, 0.0f, 0.0f, 1.0f };

			extern inline bool DefaultIsAlphaTestOn{ false };

			extern inline bool DefaultIsBlendOn{ false };
			
			extern void LoadData();
			
			extern int GetScreenWidth()
			{
				return graphicsAPISetting::ScreenSize[0];
			}

			extern int GetScreenHeight()
			{
				return graphicsAPISetting::ScreenSize[1];
			}
			
			extern float GetScreenRatio()
			{
				return graphicsAPISetting::ScreenRatio;
			}

			extern unsigned int GetMultiSamplingNum()
			{
				return graphicsAPISetting::MultiSamplingNum;
			}

		};

	}
}

