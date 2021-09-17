#pragma once

#include "Graphics_Core.h"

#include <Vector2.h>
#include <Vector4.h>

namespace doom
{
	namespace graphics
	{
		class Graphics_Setting
		{
			static inline GLFWwindow* Window{ nullptr };

			static inline bool bmIsGraphicsSettingLoaded{ false };

			static inline math::Vector<2, int> ScreenSize{};
			/// <summary>
			/// ScreenSize Width / ScreenSize Height
			/// </summary>
			static inline float ScreenRatio{};
			static inline unsigned int MultiSamplingNum;

		public:


			static inline math::Vector4 ClearColor{ 0.0f, 0.0f, 0.0f, 1.0f };

			static void LoadData();

			FORCE_INLINE static GLFWwindow* GetWindow()
			{
				return Graphics_Setting::Window;
			}

			static void SetWindow(GLFWwindow* const _window);

			FORCE_INLINE static int GetScreenWidth()
			{
				return Graphics_Setting::ScreenSize.x;
			}

			FORCE_INLINE static int GetScreenHeight()
			{
				return Graphics_Setting::ScreenSize.y;
			}

			FORCE_INLINE static math::Vector2 GetScreenSize()
			{
				return Graphics_Setting::ScreenSize;
			}

			FORCE_INLINE static float GetScreenRatio()
			{
				return Graphics_Setting::ScreenRatio;
			}

			FORCE_INLINE static unsigned int GetMultiSamplingNum()
			{
				return Graphics_Setting::MultiSamplingNum;
			}

		};

	}
}

