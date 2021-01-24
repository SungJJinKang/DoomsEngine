#pragma once
#include <vector>

#include "../Core.h"
#include "Graphics_Core.h"
#include "RenderBuffer.h"
#include "SingleTexture.h"

namespace doom
{
	namespace graphics
	{
		class FrameBuffer
		{
		private:
			static constexpr unsigned int RESERVED_RENDERBUFFER_COUNT = 3; // 
			std::vector<RenderBuffer> mAttachedRenderBuffers;

			static constexpr unsigned int RESERVED_COLOR_TEXTURE_COUNT = 3; // 
			std::vector<SingleTexture> mAttachedColorTextures;

			static constexpr unsigned int RESERVED_DEPTH_TEXTURE_COUNT = 1; // 
			std::vector<SingleTexture> mAttachedDepthextures;

			unsigned int mClearBit;

			static constexpr unsigned int RESERVED_DEPTH_STENCIL_TEXTURE_COUNT = 1; // 
			std::vector<SingleTexture> mAttachedDepthStencilTextures;

			unsigned int mWidth;
			unsigned int mHeight;

			ONLY_DEBUG(static inline unsigned int mCurrentBoundId{};)
		public:
			enum class eFrameBufferType
			{
				COLOR = GL_COLOR_BUFFER_BIT,
				DEPTH = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL = GL_STENCIL_BUFFER_BIT
			};

			unsigned int mFbo;

			FrameBuffer(unsigned int width, unsigned int height);
			virtual ~FrameBuffer();


			inline void BindFrameBuffer() noexcept
			{
				glBindFramebuffer(GL_FRAMEBUFFER, this->mFbo);

				ONLY_DEBUG(mCurrentBoundId = this->mFbo;)
			}
			static inline void UnBindFrameBuffer() noexcept
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
			}

			inline void Clear()
			{
				glClear(this->mClearBit);
			}

			enum class eImageInterpolation
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR
			};

			inline void BlitBufferTo(unsigned int DrawFrameBufferId, unsigned int srcX0, unsigned int srcY0, unsigned int srcX1, unsigned int srcY1
				, unsigned int dstX0, unsigned int dstY0, unsigned int dstX1, unsigned int dstY1, eFrameBufferType mask, eImageInterpolation filter) noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, this->mFbo);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, DrawFrameBufferId);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			inline void BlitBufferFrom(unsigned int ReadFrameBufferId, unsigned int srcX0, unsigned int srcY0, unsigned int srcX1, unsigned int srcY1
				, unsigned int dstX0, unsigned int dstY0, unsigned int dstX1, unsigned int dstY1, eFrameBufferType mask, eImageInterpolation filter) noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, ReadFrameBufferId);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->mFbo);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			void AttachRenderBuffer(eFrameBufferType renderBufferType);
			void AttachTextureBuffer(eFrameBufferType frameBufferType);

			static void CheckIsFrameBufferSuccesfullyCreated() noexcept;
		};
	}
}


