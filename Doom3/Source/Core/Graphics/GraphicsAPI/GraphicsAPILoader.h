#pragma once

#include <Core.h>

#include "GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		
		
		class D_CLASS GraphicsAPILoader : public DObject
		{
		private:

			void* mAPIModule;

			bool FreeGraphicsAPILibrary();

		public:

			GraphicsAPILoader();
			~GraphicsAPILoader();
			GraphicsAPILoader(const GraphicsAPILoader&) = delete;
			GraphicsAPILoader(GraphicsAPILoader&&) noexcept;
			GraphicsAPILoader& operator=(const GraphicsAPILoader&) = delete;
			GraphicsAPILoader& operator=(GraphicsAPILoader&&) noexcept;
			void LoadGraphicsAPILibrary(const eGraphicsAPIType graphicsAPIType);
			bool UnLoadGraphicsAPILibrary();
		};
	}
}

