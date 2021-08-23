#pragma once
#include <vector>

#include "../Core.h"
#include "../Graphics_Core.h"
#include "../GraphicsAPI.h"
#include "RenderBuffer.h"
#include "../Texture/SingleTexture.h"
#include "../OverlapBindChecker.h"
#include <ZeroResetMoveContainer.h>
namespace doom
{
	namespace graphics
	{
		class FrameBuffer
		{
			friend class Graphics_Server;
		private:

			inline static const char FRAMEBUFFER_TAG[]{ "FrameBuffer" };

			static constexpr unsigned int RESERVED_RENDERBUFFER_COUNT = 3;
			std::vector<RenderBuffer> mAttachedRenderBuffers;

			static constexpr unsigned int RESERVED_COLOR_TEXTURE_COUNT = 3;
			std::vector<SingleTexture> mAttachedColorTextures;

			static constexpr unsigned int RESERVED_DEPTH_TEXTURE_COUNT = 1; 
			std::vector<SingleTexture> mAttachedDepthTextures;

			static constexpr unsigned int RESERVED_DEPTH_STENCIL_TEXTURE_COUNT = 1; 
			std::vector<SingleTexture> mAttachedDepthStencilTextures;

			unsigned int mClearBit{ 0 };
			unsigned int mDrawTarget{ 0 };

			unsigned int mDefaultWidth;
			unsigned int mDefaultHeight;

			/// <summary>
			/// nullptr mean default ScreenBuffer
			/// </summary>
			inline static FrameBuffer* PreviousFrameBuffer{ nullptr };
			/// <summary>
			/// nullptr mean default ScreenBuffer
			/// </summary>
			inline static FrameBuffer* CurrentFrameBuffer{ nullptr };

			static void BindFrameBuffer(FrameBuffer* frameBuffer);
			
		public:
			
			BufferID mFrameBufferID{};

			FrameBuffer();
			FrameBuffer(unsigned int defaultWidth, unsigned int defaultHeight);
			virtual ~FrameBuffer();

			FrameBuffer(const FrameBuffer&) = delete;
			FrameBuffer& operator=(const FrameBuffer&) noexcept = delete;

			FrameBuffer(FrameBuffer&&) noexcept = default;
			FrameBuffer& operator=(FrameBuffer &&) noexcept = default;

			void GenerateBuffer(unsigned int defaultWidth, unsigned int defaultHeight);

			FORCE_INLINE void BindFrameBuffer() noexcept
			{
				D_ASSERT(mFrameBufferID != 0);
				FrameBuffer::BindFrameBuffer(this);
			}
			FORCE_INLINE static void UnBindFrameBuffer() noexcept
			{
				FrameBuffer::BindFrameBuffer(nullptr);
			}

			/// <summary>
			/// Rebind privous bound framebuffer
			/// </summary>
			FORCE_INLINE static void RevertFrameBuffer()
			{
				if (FrameBuffer::PreviousFrameBuffer != nullptr)
				{
					FrameBuffer::PreviousFrameBuffer->BindFrameBuffer();
				}
				else
				{
					FrameBuffer::UnBindFrameBuffer(); // bind defualt screen buffer
				}
			}

			FORCE_INLINE void Clear()
			{
				glClear(mClearBit);
			}

			enum class eImageInterpolation
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR
			};

			FORCE_INLINE void BlitBufferTo(unsigned int DrawFrameBufferId, int srcX0, int srcY0, int srcX1, int srcY1
				, int dstX0, int dstY0, int dstX1, int dstY1, GraphicsAPI::eBufferType mask, eImageInterpolation filter) noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, mFrameBufferID);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, DrawFrameBufferId);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			FORCE_INLINE void BlitBufferFrom(unsigned int ReadFrameBufferId, int srcX0, int srcY0, int srcX1, int srcY1
				, int dstX0, int dstY0, int dstX1, int dstY1, GraphicsAPI::eBufferType mask, eImageInterpolation filter) noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, ReadFrameBufferId);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBufferID);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eBufferType renderBufferType, unsigned int width, unsigned int height);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height);
			const SingleTexture& GetFrameBufferTexture(GraphicsAPI::eBufferType bufferType, unsigned int index) const;
			SingleTexture& GetFrameBufferTexture(GraphicsAPI::eBufferType bufferType, unsigned int index);

			static void CheckIsFrameBufferSuccesfullyCreated() noexcept;

			bool IsGenerated();
		};
	}
}


