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
			BufferID mRenderBufferID{};
		public:
			RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height);
			virtual ~RenderBuffer();

			RenderBuffer(const RenderBuffer&) = delete;
			RenderBuffer& operator=(const RenderBuffer&) noexcept = delete;

			RenderBuffer(RenderBuffer&&) noexcept = default;
			RenderBuffer& operator=(RenderBuffer &&) noexcept = default;
			


			inline void BindRenderBuffer() noexcept
			{
				D_CHECK_OVERLAP_BIND_AND_SAVE_BIND("RenderBuffer", this->mRenderBufferID);
				glBindRenderbuffer(GL_RENDERBUFFER, this->mRenderBufferID);
			}
			static inline void UnBindRenderBuffer() noexcept
			{
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
			}
		};
	}
}

