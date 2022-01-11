#pragma once

#include <Core.h>

#include <Simple_SingleTon/Singleton.h>
#include "GraphicsAPILoader.h"
#include "../eGraphicsAPIType.h"
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
			static eGraphicsAPIType mGraphicsAPIType;

			static void LoadGraphicsAPI(const eGraphicsAPIType graphicsAPIType);

			static void SetDefaultSettingOfAPI();

			static void GraphisAPIDebugCallBack(const char* const debugMessage, const graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity severity);

		public:
			
			static bool Initialize(const eGraphicsAPIType graphicsAPIType);
			static bool DeInitialize();

			static eGraphicsAPIType GetGraphicsAPIType();
		};

	}
}

