#pragma once
#include <vector>

#include "../Core.h"
#include "../Graphics_Core.h"
#include "../GraphicsAPI.h"
#include "RenderBuffer.h"
#include "../SingleTexture.h"
#include "../OverlapBindChecker.h"

namespace doom
{
	namespace graphics
	{
		class FrameBuffer
		{
			friend class Graphics_Server;
		private:
			static constexpr unsigned int RESERVED_RENDERBUFFER_COUNT = 3;
			std::vector<RenderBuffer> mAttachedRenderBuffers;

			static constexpr unsigned int RESERVED_COLOR_TEXTURE_COUNT = 3;
			std::vector<SingleTexture> mAttachedColorTextures;

			static constexpr unsigned int RESERVED_DEPTH_TEXTURE_COUNT = 1; 
			std::vector<SingleTexture> mAttachedDepthextures;

			static constexpr unsigned int RESERVED_DEPTH_STENCIL_TEXTURE_COUNT = 1; 
			std::vector<SingleTexture> mAttachedDepthStencilTextures;

			unsigned int mClearBit{ 0 };
			unsigned int mDrawTarget{ 0 };

			unsigned int mDefaultWidth;
			unsigned int mDefaultHeight;
		public:
			
			unsigned int mFbo{ 0 };

			FrameBuffer();
			FrameBuffer(unsigned int defaultWidth, unsigned int defaultHeight);
			void GenerateBuffer(unsigned int defaultWidth, unsigned int defaultHeight);
			virtual ~FrameBuffer();


			inline void BindFrameBuffer() noexcept
			{
				D_ASSERT(this->mFbo != 0);
				D_CHECK_OVERLAP_BIND("FramgBuffer", this->mFbo);
				glBindFramebuffer(GL_FRAMEBUFFER, this->mFbo);
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

			inline void BlitBufferTo(unsigned int DrawFrameBufferId, int srcX0, int srcY0, int srcX1, int srcY1
				, int dstX0, int dstY0, int dstX1, int dstY1, GraphicsAPI::eBufferType mask, eImageInterpolation filter) noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, this->mFbo);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, DrawFrameBufferId);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			inline void BlitBufferFrom(unsigned int ReadFrameBufferId, int srcX0, int srcY0, int srcX1, int srcY1
				, int dstX0, int dstY0, int dstX1, int dstY1, GraphicsAPI::eBufferType mask, eImageInterpolation filter) noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, ReadFrameBufferId);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->mFbo);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			void AttachRenderBuffer(GraphicsAPI::eBufferType renderBufferType, unsigned int width, unsigned int height);
			void AttachTextureBuffer(GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height);

			static void CheckIsFrameBufferSuccesfullyCreated() noexcept;

			bool IsGenerated();
		};
	}
}


