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
			static inline const char* RENDERBUFFER_TAG = "RenderBuffer";
			BufferID mRenderBufferID{};
		public:
			RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height);
			virtual ~RenderBuffer();

			RenderBuffer(const RenderBuffer&) = delete;
			RenderBuffer& operator=(const RenderBuffer&) noexcept = delete;

			RenderBuffer(RenderBuffer&&) noexcept = default;
			RenderBuffer& operator=(RenderBuffer &&) noexcept = default;
			
			inline static void BindRenderBuffer(int renderBufferID)
			{
				if (OverlapBindChecker::GetBoundID(RENDERBUFFER_TAG) != renderBufferID)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(RENDERBUFFER_TAG, renderBufferID);
					glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
				}
			}

			inline void BindRenderBuffer() noexcept
			{
				BindRenderBuffer(this->mRenderBufferID);
			}
			static inline void UnBindRenderBuffer() noexcept
			{
				BindRenderBuffer(0);
			}
		};
	}
}

