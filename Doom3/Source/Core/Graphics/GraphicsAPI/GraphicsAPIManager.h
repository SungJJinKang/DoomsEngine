#pragma once

#include <Core.h>

#include "GraphicsAPILoader.h"

namespace dooms
{
	namespace graphics
	{
		class GraphicsAPILoader;
		class GraphicsAPIManager : public DObject
		{
		private:

			GraphicsAPILoader mGraphicsAPILoader;

			void LoadGraphicsAPI(const eGraphicsAPIType graphicsAPIType);

			void SetDefaultSettingOfAPI();

		public:


			GraphicsAPIManager();
			~GraphicsAPIManager();
			GraphicsAPIManager(const GraphicsAPIManager&) = delete;
			GraphicsAPIManager(GraphicsAPIManager&&) noexcept;
			GraphicsAPIManager& operator=(const GraphicsAPIManager&) = delete;
			GraphicsAPIManager& operator=(GraphicsAPIManager&&) noexcept;

			void Initialize(const eGraphicsAPIType graphicsAPIType);
			void DeInitialize();
		};

	}
}

