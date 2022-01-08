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

