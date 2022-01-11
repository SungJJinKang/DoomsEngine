#pragma once
#include <vector>

#include "../Core.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "../GraphicsAPI/graphicsAPISetting.h"
#include "RenderBuffer.h"
#include "../Texture/SingleTexture.h"
#include "../OverlapBindChecker.h"
#include "../Buffer/BufferID.h"

#include "FrameBuffer.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS FrameBuffer : public DObject
		{
			GENERATE_BODY()
			

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

			std::vector<GraphicsAPI::eBufferMode> mTargetDrawBufferContainer;

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

			void OnSetPendingKill() override;
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
						BindFrameBufferStatic(GraphicsAPI::FRAMEBUFFER, 0);
						GraphicsAPI::SetViewport(0, 0, graphics::graphicsAPISetting::GetScreenWidth(), graphics::graphicsAPISetting::GetScreenHeight());
					}
					else
					{
						BindFrameBufferStatic(GraphicsAPI::FRAMEBUFFER, frameBuffer->mFrameBufferID);
						GraphicsAPI::SetViewport(0, 0, frameBuffer->mDefaultWidth, frameBuffer->mDefaultHeight);
					}
					FrameBuffer::CurrentFrameBuffer = frameBuffer;
				}
			}

			FORCE_INLINE void BindFrameBuffer() const noexcept
			{
				D_ASSERT(mFrameBufferID.IsValid());
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
				GraphicsAPI::ClearBuffer(mClearBit);
			}

			
			
			FORCE_INLINE static void BindFrameBufferStatic(const GraphicsAPI::eBindFrameBufferTarget bindFrameBufferTarget, const UINT32 frameBufferID)
			{
				GraphicsAPI::BindFrameBuffer(frameBufferID, bindFrameBufferTarget);
			}
			
			static void BlitFrameBufferTo(
				UINT32 ReadFrameBufferId, UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1,
				INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1,
				GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter) noexcept;

			void BlitFrameBufferTo(
				UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1, 
				INT32 srcY1 , INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
				GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter) const noexcept;

			void BlitFrameBufferFrom(UINT32 ReadFrameBufferId, INT32 srcX0, INT32 srcY0, 
				INT32 srcX1, INT32 srcY1 , INT32 dstX0, INT32 dstY0, INT32 dstX1, 
				INT32 dstY1, GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter) const noexcept;

			void BlitFrameBufferToTexture(
				dooms::graphics::Texture* const drawTexture, INT32 srcX0, INT32 srcY0, INT32 srcX1,
				INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1,
				GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter) const noexcept;

			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType, UINT32 width, UINT32 height);
			RenderBuffer& AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height);
			SingleTexture& AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType);
			const SingleTexture* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index) const;
			SingleTexture* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index);

			void CheckIsFrameBufferSuccesfullyCreated() noexcept;

			bool IsGenerated();

			
			INT32 GetFrameBufferWidth() const;
			INT32 GetFrameBufferHeight() const;

			/*
			 *INT32 GetFrameBufferParameteriv
			(
				const eFrameBufferParameterPName frameBufferParameterPName
			) const;

			static INT32 GetFrameBufferParameterivStatic
			(
				const FrameBuffer* const frameBuffer,
				const eFrameBufferParameterPName frameBufferParameterPName
			);
			*/
		};
	}
}


