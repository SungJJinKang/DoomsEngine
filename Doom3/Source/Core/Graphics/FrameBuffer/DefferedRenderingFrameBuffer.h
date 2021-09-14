#pragma once

#include "FrameBuffer.h"

namespace doom
{
	namespace graphics
	{
		class DefferedRenderingFrameBuffer : public graphics::FrameBuffer
		{

		private:

		public:

			DefferedRenderingFrameBuffer();

			void BindGBufferTextures();

		};

	}
}

