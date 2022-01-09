#pragma once

#include "GraphicsAPI.h"
#include "GraphicsAPI.h"

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
			
			

			extern inline bool DefaultIsAlphaTestOn{ false };

			extern inline bool DefaultIsBlendOn{ false };

			extern inline graphics::GraphicsAPI::eBlendFactor DefaultBlendSourceFactor = GraphicsAPI::eBlendFactor::SRC_ALPHA;
			extern inline graphics::GraphicsAPI::eBlendFactor DefaultBlendDestinationFactor = GraphicsAPI::eBlendFactor::ONE_MINUS_SRC_ALPHA;
			
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

