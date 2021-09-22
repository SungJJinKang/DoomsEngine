#pragma once
#include <vector>

#include "../Core.h"
#include "../Graphics_Core.h"
#include "../Graphics_Setting.h"
#include "../GraphicsAPI.h"
#include "RenderBuffer.h"
#include "../Texture/SingleTexture.h"
#include "../OverlapBindChecker.h"
#include "../Buffer/BufferID.h"

namespace doom
{
	namespace graphics
	{
		class FrameBuffer
		{
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

			std::vector<unsigned int> mTargetDrawBufferContainer;

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


		public:
			
			BufferID mFrameBufferID;

			FrameBuffer();
			FrameBuffer(unsigned int defaultWidth, unsigned int defaultHeight);
			virtual ~FrameBuffer();

			FrameBuffer(const FrameBuffer&) = delete;
			FrameBuffer& operator=(const FrameBuffer&) noexcept = delete;

			FrameBuffer(FrameBuffer&&) noexcept = default;
			FrameBuffer& operator=(FrameBuffer &&) noexcept = default;

			void GenerateBuffer(unsigned int defaultWidth, unsigned int defaultHeight);
			void RefreshTargetDrawBufferContainer();
			void SetTargetDrawBuffer();

			FORCE_INLINE unsigned int GetDefaultWidth() const
			{
				return mDefaultWidth;
			}

			FORCE_INLINE unsigned int GetDefaultHeight() const
			{
				return mDefaultHeight;
			}

			FORCE_INLINE static void StaticBindFrameBuffer(FrameBuffer* const frameBuffer)
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(FRAMEBUFFER_TAG, ((frameBuffer != nullptr) ? frameBuffer->mFrameBufferID.Get() : 0)))
				{
					FrameBuffer::PreviousFrameBuffer = CurrentFrameBuffer;
					if (frameBuffer == nullptr)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, 0);
						glViewport(0, 0, graphics::Graphics_Setting::GetScreenWidth(), graphics::Graphics_Setting::GetScreenHeight());
					}
					else
					{
						glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->mFrameBufferID);
						glViewport(0, 0, frameBuffer->mDefaultWidth, frameBuffer->mDefaultHeight);
					}
					FrameBuffer::CurrentFrameBuffer = frameBuffer;
				}
			}

			FORCE_INLINE void BindFrameBuffer() noexcept
			{
				D_ASSERT(mFrameBufferID != 0);
				D_ASSERT(mDefaultWidth != 0 && mDefaultHeight != 0);
				FrameBuffer::StaticBindFrameBuffer(this);
			}
			FORCE_INLINE static void UnBindFrameBuffer()  noexcept 
			{
				FrameBuffer::StaticBindFrameBuffer(nullptr); // bind MainFrameBuffer
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

			FORCE_INLINE virtual void ClearFrameBuffer()
			{
				GraphicsAPI::Clear(mClearBit);
			}

			enum class eImageInterpolation
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR
			};

			FORCE_INLINE void BlitBufferTo(unsigned int DrawFrameBufferId, int srcX0, int srcY0, int srcX1, int srcY1
				, int dstX0, int dstY0, int dstX1, int dstY1, GraphicsAPI::eBufferBitType mask, eImageInterpolation filter) const noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, mFrameBufferID);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, DrawFrameBufferId);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			FORCE_INLINE void BlitBufferFrom(unsigned int ReadFrameBufferId, int srcX0, int srcY0, int srcX1, int srcY1
				, int dstX0, int dstY0, int dstX1, int dstY1, GraphicsAPI::eBufferBitType mask, eImageInterpolation filter) const noexcept
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, ReadFrameBufferId);
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBufferID);
				glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<unsigned int>(mask), static_cast<unsigned int>(filter));
			}

			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType, unsigned int width, unsigned int height);
			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType, unsigned int width, unsigned int height);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType);
			const SingleTexture* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, unsigned int index) const;
			SingleTexture* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, unsigned int index);

			void CheckIsFrameBufferSuccesfullyCreated() noexcept;

			bool IsGenerated();
		};
	}
}


