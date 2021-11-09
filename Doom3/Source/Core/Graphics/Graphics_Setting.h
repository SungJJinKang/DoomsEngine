#pragma once

#include <Vector2.h>
#include <Vector4.h>
#include "Color.h"
#include "GraphicsAPI.h"

struct GLFWwindow;

namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS Graphics_Setting
		{
			static inline GLFWwindow* Window{ nullptr };

			static inline math::Vector2Int ScreenSize{};
			/// <summary>
			/// ScreenSize Width / ScreenSize Height
			/// </summary>
			static inline FLOAT32 ScreenRatio{};
			static inline UINT32 MultiSamplingNum;

		public:

			static inline bool IsSortObjectFrontToBack{ true };

			static inline bool IsDrawDebuggersEnabled{ true };
			static inline eColor DrawDebuggersDefualtColor{ eColor::Green };

			static inline bool IsOverDrawVisualizationEnabled{ false };

			static inline bool DrawRenderingBoundingBox{ false };
			static inline math::Vector4 DefaultClearColor{ 0.0f, 0.0f, 0.0f, 1.0f };

			static inline bool DefaultIsAlphaTestOn{ false };

			static inline bool DefaultIsBlendOn{ false };
			static inline GraphicsAPI::eSourceFactor DefaultBlendSourceFactor{ GraphicsAPI::eSourceFactor::SRC_ALPHA };
			static inline GraphicsAPI::eDestinationFactor DefaultBlendDestinationFactor{ GraphicsAPI::eDestinationFactor::ONE_MINUS_SRC_ALPHA };

			static inline GraphicsAPI::eDepthFuncType DefualtDepthFuncType{ GraphicsAPI::eDepthFuncType::LESS };

			static void LoadData();

			FORCE_INLINE static GLFWwindow* GetWindow()
			{
				return Graphics_Setting::Window;
			}

			static void SetWindow(GLFWwindow* const _window);

			FORCE_INLINE static INT32 GetScreenWidth()
			{
				return Graphics_Setting::ScreenSize.x;
			}

			FORCE_INLINE static INT32 GetScreenHeight()
			{
				return Graphics_Setting::ScreenSize.y;
			}

			FORCE_INLINE static math::Vector2 GetScreenSize()
			{
				return Graphics_Setting::ScreenSize;
			}

			FORCE_INLINE static FLOAT32 GetScreenRatio()
			{
				return Graphics_Setting::ScreenRatio;
			}

			FORCE_INLINE static UINT32 GetMultiSamplingNum()
			{
				return Graphics_Setting::MultiSamplingNum;
			}

		};

	}
}

