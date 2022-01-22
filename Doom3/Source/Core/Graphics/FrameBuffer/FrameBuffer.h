#pragma once
#include <vector>

#include "../Core.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "../GraphicsAPI/graphicsAPISetting.h"
#include "RenderBuffer.h"
#include "../OverlapBindChecker.h"
#include "../Buffer/BufferID.h"

#include "FrameBuffer.reflection.h"
namespace dooms
{
	namespace asset
	{
		class TextureAsset;
	}

	namespace graphics
	{
		class DOOM_API D_CLASS FrameBuffer : public DObject
		{
			GENERATE_BODY()
			

		private:

			struct FrameBufferTextureAndRenderTargetView
			{
				asset::TextureAsset* mTextureResource;
				BufferID mRenderTargetView;
				INT32 mBindingPosition;

				FrameBufferTextureAndRenderTargetView()
					: mTextureResource(nullptr), mRenderTargetView(), mBindingPosition(-1)
				{
					
				}
				FrameBufferTextureAndRenderTargetView
				(
					asset::TextureAsset* const _textureResource,
					BufferID _renderTargetView,
					INT32 bindingPosition = -1
				)
					: mTextureResource(_textureResource), mRenderTargetView(_renderTargetView), mBindingPosition(mBindingPosition)
				{
					D_ASSERT(_textureResource != nullptr);
					D_ASSERT(_renderTargetView.IsValid());
				}

				FrameBufferTextureAndRenderTargetView(const FrameBufferTextureAndRenderTargetView&) = default;
				FrameBufferTextureAndRenderTargetView(FrameBufferTextureAndRenderTargetView&&) noexcept = default;
				FrameBufferTextureAndRenderTargetView& operator=(const FrameBufferTextureAndRenderTargetView&) = default;
				FrameBufferTextureAndRenderTargetView& operator=(FrameBufferTextureAndRenderTargetView&&) noexcept = default;
				
				bool IsValid() const
				{
					return (mTextureResource != nullptr);
				}
			};

			inline static const char FRAMEBUFFER_TAG[]{ "FrameBuffer" };
			
			/*
			static constexpr UINT32 RESERVED_RENDERBUFFER_COUNT = 3;
			std::vector<RenderBuffer> mAttachedRenderBuffers;
			*/
			
			std::vector<FrameBufferTextureAndRenderTargetView> mAttachedColorTextures;
			FrameBufferTextureAndRenderTargetView mAttachedDepthStencilTexture;

			BufferID mFrameBufferIDForOPENGL;
			
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

			FrameBuffer(const FrameBuffer&) = delete;
			FrameBuffer& operator=(const FrameBuffer&) noexcept = delete;

			FrameBuffer(FrameBuffer&&) noexcept = default;
			FrameBuffer& operator=(FrameBuffer &&) noexcept = default;

			void GenerateBuffer();

			FORCE_INLINE UINT32 GetDefaultWidth() const
			{
				return mDefaultWidth;
			}

			FORCE_INLINE UINT32 GetDefaultHeight() const
			{
				return mDefaultHeight;
			}

			static void StaticBindFrameBuffer(const FrameBuffer* const frameBuffer);
			void BindFrameBuffer() const noexcept;
			static void UnBindFrameBuffer() noexcept;
			static void RevertFrameBuffer();

			/*
			virtual void ClearFrameBuffer() const;
			*/
			
			
			static void BlitFrameBufferTo
			(
				dooms::asset::TextureAsset* const readFrameBuffer, dooms::asset::TextureAsset* const drawFrameBuffer,
				INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1,
				INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1,
				GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter
			) noexcept;


			//RenderBuffer& AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType, UINT32 width, UINT32 height);
			//RenderBuffer& AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType);
			dooms::asset::TextureAsset* AttachTextureBuffer
			(
				GraphicsAPI::eBufferBitType frameBufferType,
				UINT32 bindingPosition,
				UINT32 width, 
				UINT32 height
			);
			const asset::TextureAsset* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, INT32 bindingPosition) const;
			asset::TextureAsset* GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, INT32 bindingPosition);
			
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


