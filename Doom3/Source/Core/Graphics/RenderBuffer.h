#pragma once
#include "Graphics_Core.h"

namespace doom
{
	namespace graphics
	{
		class FrameBuffer;
		enum FrameBuffer::eFrameBufferType;

		class RenderBuffer
		{
		private:
			unsigned int mID;
		public:
			RenderBuffer(FrameBuffer& ownerFrameBuffer, FrameBuffer::eFrameBufferType frameBufferType, unsigned int width, unsigned int height);
			inline void BindRenderBuffer() noexcept
			{
				glBindRenderbuffer(GL_RENDERBUFFER, this->mID);
			}
			static inline void UnBindRenderBuffer() noexcept
			{
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
			}
		};
	}
}

