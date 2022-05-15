#pragma once

#include "GraphicsAPI.h"
#include "GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		enum class eDepthPrePassType
		{
			Disable,
			AllOpaque
		};

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

			extern graphics::GraphicsAPI::eBlendFactor DefaultBlendSourceFactor;
			extern graphics::GraphicsAPI::eBlendFactor DefaultBlendDestinationFactor;
			extern graphics::eDepthPrePassType DepthPrePassType;
			
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

