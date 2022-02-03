#pragma once

#include <Core.h>

#include <Simple_SingleTon/Singleton.h>
#include "GraphicsAPILoader.h"
#include "../GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		

		class GraphicsAPILoader;
		class GraphicsAPIManager : public DObject, public ISingleton<GraphicsAPIManager>
		{
		private:

			static GraphicsAPILoader mGraphicsAPILoader;

			static void LoadGraphicsAPI(const GraphicsAPI::eGraphicsAPIType graphicsAPIType);

			static void SetDefaultSettingOfAPI();

			static void GraphisAPIDebugCallBack(const char* const debugMessage, const graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity severity);

		public:
			
			static bool Initialize(const GraphicsAPI::eGraphicsAPIType graphicsAPIType);
			static bool DeInitialize();

			FORCE_INLINE static GraphicsAPI::eGraphicsAPIType GetCurrentAPIType()
			{
				static const GraphicsAPI::eGraphicsAPIType currentGraphicsAPIType = graphics::GraphicsAPI::_GetCurrentAPIType();

				D_ASSERT(currentGraphicsAPIType == GraphicsAPI::eGraphicsAPIType::DX11_10 || currentGraphicsAPIType == GraphicsAPI::eGraphicsAPIType::OpenGL);

				return currentGraphicsAPIType;
			}
		};

	}
}

