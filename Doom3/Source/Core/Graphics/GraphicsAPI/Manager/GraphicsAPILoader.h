#pragma once

#include <Core.h>

#include "../GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		
		
		class D_CLASS GraphicsAPILoader : public DObject
		{
		private:

			void* mAPIModule;

			void FetchExportedFunctionAddress();
			unsigned int FreeGraphicsAPILibrary();

		public:

			GraphicsAPILoader();
			~GraphicsAPILoader();
			GraphicsAPILoader(const GraphicsAPILoader&) = delete;
			GraphicsAPILoader(GraphicsAPILoader&&) noexcept;
			GraphicsAPILoader& operator=(const GraphicsAPILoader&) = delete;
			GraphicsAPILoader& operator=(GraphicsAPILoader&&) noexcept;
			void* LoadGraphicsAPILibrary(const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType);
			bool UnLoadGraphicsAPILibrary();
		};
	}
}

