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
			DOBJECT_CLASS_BODY(FrameBuffer);

		private:

			inline static const char FRAMEBUFFER_TAG[]{ "FrameBuffer" };


			BufferID mFrameBufferID;

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
			inline static const FrameBuffer* PreviousFrameBuffer{ nullptr };
			/// <summary>
			/// nullptr mean default ScreenBuffer
			/// </summary>
			inline static const FrameBuffer* CurrentFrameBuffer{ nullptr };

			void DestoryFrameBufferObject();

		public:
			
		

			FrameBuffer();
			FrameBuffer(UINT32 defaultWidth, UINT32 defaultHeight);
			virtual ~FrameBuffer();

			FrameBuffer(const FrameBuffer&);
			FrameBuffer& operator=(const FrameBuffer&) noexcept = delete;

			FrameBuffer(FrameBuffer&&) noexcept = default;
			FrameBuffer& operator=(FrameBuffer &&) noexcept = default;

			void GenerateBuffer(UINT32 defaultWidth, UINT32 defaultHeight);
			void RefreshTargetDrawBufferContainer();
			void SetTargetDrawBuffer();

			FORCE_INLINE const BufferID& GetFrameBufferID() const
			{
				return mFrameBufferID;
			}

			FORCE_INLINE UINT32 GetDefaultWidth() const
			{
				return mDefaultWidth;
			}

			FORCE_INLINE UINT32 GetDefaultHeight() const
			{
				return mDefaultHeight;
			}

			FORCE_INLINE static void StaticBindFrameBuffer(const FrameBuffer* const frameBuffer)
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(FRAMEBUFFER_TAG, ((frameBuffer != nullptr) ? frameBuffer->mFrameBufferID.GetBufferID() : 0)))
				{
					FrameBuffer::PreviousFrameBuffer = CurrentFrameBuffer;
					if (frameBuffer == nullptr)
					{
						BindFrameBufferStatic(eBindFrameBufferTarget::FRAMEBUFFER, 0);
						glViewport(0, 0, graphics::Graphics_Setting::GetScreenWidth(), graphics::Graphics_Setting::GetScreenHeight());
					}
					else
					{
						BindFrameBufferStatic(eBindFrameBufferTarget::FRAMEBUFFER, frameBuffer->mFrameBufferID);
						glViewport(0, 0, frameBuffer->mDefaultWidth, frameBuffer->mDefaultHeight);
					}
					FrameBuffer::CurrentFrameBuffer = frameBuffer;
				}
			}

			FORCE_INLINE void BindFrameBuffer() const noexcept
			{
				D_ASSERT(mFrameBufferID != 0);
				D_ASSERT(mDefaultWidth != 0 && mDefaultHeight != 0);
				FrameBuffer::StaticBindFrameBuffer(this);
			}
			FORCE_INLINE static void UnBindFrameBuffer() noexcept 
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

			FORCE_INLINE virtual void ClearFrameBuffer() const
			{
				GraphicsAPI::Clear(mClearBit);
			}

			enum class eImageInterpolation
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR
			};

			enum class eBindFrameBufferTarget : UINT32
			{
				DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
				READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
				FRAMEBUFFER = GL_FRAMEBUFFER
			};

			FORCE_INLINE static void BindFrameBufferStatic(const eBindFrameBufferTarget bindFrameBufferTarget, const UINT32 frameBufferID)
			{
				glBindFramebuffer(static_cast<UINT32>(bindFrameBufferTarget), frameBufferID);
			}
			
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


			enum class eFrameBufferParameterPName : UINT32
			{
				FRAMEBUFFER_DEFAULT_WIDTH = GL_FRAMEBUFFER_DEFAULT_WIDTH,
				FRAMEBUFFER_DEFAULT_HEIGHT = GL_FRAMEBUFFER_DEFAULT_HEIGHT,
				FRAMEBUFFER_DEFAULT_SAMPLES = GL_FRAMEBUFFER_DEFAULT_SAMPLES,
				FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS = GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
			};

			INT32 GetFrameBufferParameteriv
			(
				const eFrameBufferParameterPName frameBufferParameterPName
			) const;

			static INT32 GetFrameBufferParameterivStatic
			(
				const FrameBuffer* const frameBuffer,
				const eFrameBufferParameterPName frameBufferParameterPName
			);
		};
	}
}


