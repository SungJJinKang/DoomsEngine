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
			static inline const char RENDERBUFFER_TAG[]{ "RenderBuffer" };
			BufferID mRenderBufferID{};
		public:
			RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height);
			virtual ~RenderBuffer();

			RenderBuffer(const RenderBuffer&) = delete;
			RenderBuffer& operator=(const RenderBuffer&) noexcept = delete;

			RenderBuffer(RenderBuffer&&) noexcept = default;
			RenderBuffer& operator=(RenderBuffer &&) noexcept = default;
			
			FORCE_INLINE static void BindRenderBuffer(int renderBufferID)
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(RENDERBUFFER_TAG, renderBufferID))
				{
					glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
				}
			}

			FORCE_INLINE void BindRenderBuffer() noexcept
			{
				BindRenderBuffer(mRenderBufferID);
			}
			FORCE_INLINE static void UnBindRenderBuffer() noexcept
			{
				BindRenderBuffer(0);
			}
		};
	}
}

