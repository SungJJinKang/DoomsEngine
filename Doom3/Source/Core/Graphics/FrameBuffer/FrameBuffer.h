#pragma once
#include <vector>

#include "../Core.h"
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
		class FrameBuffer : public DObject
		{
		private:

			inline static const char FRAMEBUFFER_TAG[]{ "FrameBuffer" };

			static constexpr UINT32 RESERVED_RENDERBUFFER_COUNT = 3;
			std::vector<RenderBuffer> mAttachedRenderBuffers;

			static constexpr UINT32 RESERVED_COLOR_TEXTURE_COUNT = 3;
			std::vector<SingleTexture> mAttachedColorTextures;

			static constexpr UINT32 RESERVED_DEPTH_TEXTURE_COUNT = 1; 
			std::vector<SingleTexture> mAttachedDepthTextures;

			static constexpr UINT32 RESERVED_DEPTH_STENCIL_TEXTURE_COUNT = 1; 
			std::vector<SingleTexture> mAttachedDepthStencilTextures;

			std::vector<UINT32> mTargetDrawBufferContainer;

			UINT32 mClearBit{ 0 };
			UINT32 mDrawTarget{ 0 };

			UINT32 mDefaultWidth;
			UINT32 mDefaultHeight;

			/// <summary>
			/// nullptr mean default ScreenBuffer
			/// </summary>
			inline static FrameBuffer* PreviousFrameBuffer{ nullptr };
			/// <summary>
			/// nullptr mean default ScreenBuffer
			/// </summary>
			inline static FrameBuffer* CurrentFrameBuffer{ nullptr };

			void DestoryFrameBufferObject();

		public:
			
			BufferID mFrameBufferID;

			FrameBuffer();
			FrameBuffer(UINT32 defaultWidth, UINT32 defaultHeight);
			virtual ~FrameBuffer();

			FrameBuffer(const FrameBuffer&) = delete;
			FrameBuffer& operator=(const FrameBuffer&) noexcept = delete;

			FrameBuffer(FrameBuffer&&) noexcept = default;
			FrameBuffer& operator=(FrameBuffer &&) noexcept = default;

			void GenerateBuffer(UINT32 defaultWidth, UINT32 defaultHeight);
			void RefreshTargetDrawBufferContainer();
			void SetTargetDrawBuffer();
		

			FORCE_INLINE UINT32 GetDefaultWidth() const
			{
				return mDefaultWidth;
			}

			FORCE_INLINE UINT32 GetDefaultHeight() const
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
						doom::graphics::GraphicsAPI::BindFrameBuffer(doom::graphics::GraphicsAPI::eBindFrameBufferTarget::FRAMEBUFFER, 0);
						glViewport(0, 0, graphics::Graphics_Setting::GetScreenWidth(), graphics::Graphics_Setting::GetScreenHeight());
					}
					else
					{
						doom::graphics::GraphicsAPI::BindFrameBuffer(doom::graphics::GraphicsAPI::eBindFrameBufferTarget::FRAMEBUFFER, frameBuffer->mFrameBufferID);
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
			
			static void BlitFrameBufferTo(
				UINT32 ReadFrameBufferId, UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1,
				INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1,
				GraphicsAPI::eBufferBitType mask, eImageInterpolation filter) noexcept;

			void BlitFrameBufferTo(
				UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1, 
				INT32 srcY1 , INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
				GraphicsAPI::eBufferBitType mask, eImageInterpolation filter) const noexcept;

			void BlitFrameBufferFrom(UINT32 ReadFrameBufferId, INT32 srcX0, INT32 srcY0, 
				INT32 srcX1, INT32 srcY1 , INT32 dstX0, INT32 dstY0, INT32 dstX1, 
				INT32 dstY1, GraphicsAPI::eBufferBitType mask, eImageInterpolation filter) const noexcept;

			void BlitFrameBufferToTexture(
				doom::graphics::Texture* const drawTexture, INT32 srcX0, INT32 srcY0, INT32 srcX1,
				INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1,
				GraphicsAPI::eBufferBitType mask, eImageInterpolation filter) const noexcept;

			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType, UINT32 width, UINT32 height);
			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType);
			const SingleTexture* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index) const;
			SingleTexture* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index);

			void CheckIsFrameBufferSuccesfullyCreated() noexcept;

			bool IsGenerated();
		};
	}
}


