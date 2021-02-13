#pragma once
#include "../Graphics_Core.h"
#include "../GraphicsAPI.h"
#include "../OverlapBindChecker.h"
namespace doom
{
	namespace graphics
	{
		class FrameBuffer;

		class RenderBuffer
		{
		private:
			unsigned int mID;
		public:
			RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height);
			inline void BindRenderBuffer() noexcept
			{
				D_CHECK_OVERLAP_BIND("RenderBuffer", this->mID);
				glBindRenderbuffer(GL_RENDERBUFFER, this->mID);
			}
			static inline void UnBindRenderBuffer() noexcept
			{
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
			}
		};
	}
}

