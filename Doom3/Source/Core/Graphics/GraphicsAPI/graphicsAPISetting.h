#pragma once

#include "GraphicsAPI.h"
#include "GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		namespace graphicsAPISetting
		{
			extern int ScreenSize[2];
			/// <summary>
			/// ScreenSize Width / ScreenSize Height
			/// </summary>
			extern float ScreenRatio;
			extern unsigned int MultiSamplingNum;
			
			

			extern bool DefaultIsAlphaTestOn;

			extern bool DefaultIsBlendOn;

			extern inline graphics::GraphicsAPI::eBlendFactor DefaultBlendSourceFactor = GraphicsAPI::eBlendFactor::SRC_ALPHA;
			extern inline graphics::GraphicsAPI::eBlendFactor DefaultBlendDestinationFactor = GraphicsAPI::eBlendFactor::ONE_MINUS_SRC_ALPHA;
			
			extern void LoadData();
			
			inline extern int GetScreenWidth()
			{
				return graphicsAPISetting::ScreenSize[0];
			}

			inline extern int GetScreenHeight()
			{
				return graphicsAPISetting::ScreenSize[1];
			}
			
			inline extern float GetScreenRatio()
			{
				return graphicsAPISetting::ScreenRatio;
			}

			inline extern unsigned int GetMultiSamplingNum()
			{
				return graphicsAPISetting::MultiSamplingNum;
			}

		};

	}
}

