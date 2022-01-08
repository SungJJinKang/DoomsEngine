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

		public:

			GraphicsAPILoader mGraphicsAPILoader;

			GraphicsAPIManager();
			~GraphicsAPIManager();
			GraphicsAPIManager(const GraphicsAPIManager&) = delete;
			GraphicsAPIManager(GraphicsAPIManager&&) noexcept;
			GraphicsAPIManager& operator=(const GraphicsAPIManager&) = delete;
			GraphicsAPIManager& operator=(GraphicsAPIManager&&) noexcept;
		};

	}
}

