#pragma once

#include <Core.h>

#include "eGraphicsAPIType.h"

namespace dooms
{
	namespace graphics
	{
		
		
		class D_CLASS GraphicsAPILoader : public DObject
		{
		private:

			void* mAPIModule;

			unsigned int FreeGraphicsAPILibrary();

		public:

			GraphicsAPILoader();
			~GraphicsAPILoader();
			GraphicsAPILoader(const GraphicsAPILoader&) = delete;
			GraphicsAPILoader(GraphicsAPILoader&&) noexcept;
			GraphicsAPILoader& operator=(const GraphicsAPILoader&) = delete;
			GraphicsAPILoader& operator=(GraphicsAPILoader&&) noexcept;
			void* LoadGraphicsAPILibrary(const eGraphicsAPIType graphicsAPIType);
			bool UnLoadGraphicsAPILibrary();
		};
	}
}

