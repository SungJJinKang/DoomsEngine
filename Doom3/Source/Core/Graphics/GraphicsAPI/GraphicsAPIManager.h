#pragma once

#include <Core.h>

#include <Simple_SingleTon/Singleton.h>
#include "GraphicsAPILoader.h"
#include "eGraphicsAPIType.h"

namespace dooms
{
	namespace graphics
	{
		

		class GraphicsAPILoader;
		class GraphicsAPIManager : public DObject, public ISingleton<GraphicsAPIManager>
		{
		private:

			GraphicsAPILoader mGraphicsAPILoader;
			eGraphicsAPIType mGraphicsAPIType = eGraphicsAPIType::GraphicsAPIType_NONE;

			void LoadGraphicsAPI(const eGraphicsAPIType graphicsAPIType);

			void SetDefaultSettingOfAPI();

			static void GraphisAPIDebugCallBack(const char* const debugMessage, const graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity severity);

		public:


			GraphicsAPIManager();
			~GraphicsAPIManager();
			GraphicsAPIManager(const GraphicsAPIManager&) = delete;
			GraphicsAPIManager(GraphicsAPIManager&&) noexcept;
			GraphicsAPIManager& operator=(const GraphicsAPIManager&) = delete;
			GraphicsAPIManager& operator=(GraphicsAPIManager&&) noexcept;

			void Initialize(const eGraphicsAPIType graphicsAPIType);
			void DeInitialize();

			eGraphicsAPIType GetGraphicsAPIType() const;
		};

	}
}

