#pragma once
#include <vector>

#include "../Core.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "FrameBufferView.h"

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
			

			inline static const char FRAMEBUFFER_TAG[]{ "FrameBuffer" };
			
			/*
			static constexpr UINT32 RESERVED_RENDERBUFFER_COUNT = 3;
			std::vector<RenderBuffer> mAttachedRenderBuffers;
			*/

			D_PROPERTY()
			std::vector<FrameBufferView*> mAttachedColorTextureViews;

			D_PROPERTY()
			FrameBufferView* mAttachedDepthStencilTextureView;

			D_PROPERTY()
			BufferID mFrameBufferIDForOPENGL;

			D_PROPERTY()
			UINT32 mDefaultWidth;
			D_PROPERTY()
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

			void GenerateFrameBuffer();
			
			BufferID GetFrameBufferIDForOPENGL() const;

			FORCE_INLINE UINT32 GetDefaultWidth() const
			{
				return mDefaultWidth;
			}

			FORCE_INLINE UINT32 GetDefaultHeight() const
			{
				return mDefaultHeight;
			}

			static void StaticBindFrameBuffer(const FrameBuffer* const frameBuffer);
			static void StaticBindBackFrameBuffer();
			void BindFrameBuffer() const noexcept;
			static void RevertFrameBuffer();

			/*
			virtual void ClearFrameBuffer() const;
			*/
			
			
			static void BlitFrameBufferFromToFrameBuffer
			(
				dooms::graphics::FrameBuffer* const fromFrameBuffer, dooms::graphics::FrameBuffer* const toFrameBuffer,
				INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1,
				INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1,
				GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter
			) noexcept;


			//RenderBuffer& AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType, UINT32 width, UINT32 height);
			//RenderBuffer& AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType);
			dooms::asset::TextureAsset* AttachColorTextureToFrameBuffer
			(
				UINT32 bindingPosition,
				UINT32 width, 
				UINT32 height
			);
			dooms::asset::TextureAsset* AttachDepthTextureToFrameBuffer
			(
				UINT32 width,
				UINT32 height
			);
			dooms::asset::TextureAsset* AttachDepthStencilTextureToFrameBuffer
			(
				UINT32 width,
				UINT32 height
			);

			size_t GetAttachedColorTextureCount() const;
			dooms::asset::TextureAsset* GetColorTextureResourceObject(const UINT32 bindingPosition) const;
			dooms::asset::TextureAsset* GetDepthTextureResourceObject() const;
			dooms::asset::TextureAsset* GetDepthStencilTextureResourceObject() const;
			FrameBufferView* GetColorTextureRenderTargetView(const UINT32 bindingPosition) const;
			FrameBufferView* GetDepthTextureRenderTargetView() const;
			FrameBufferView* GetDepthStencilTextureRenderTargetView() const;
			RenderingTextureViewProxy* GetColorTextureView(const UINT32 bindingPosition, const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage) const;
			RenderingTextureViewProxy* GetDepthTextureView(const UINT32 bindingPosition, const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage) const;
			RenderingTextureViewProxy* GetDepthStencilTextureView(const UINT32 bindingPosition, const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage) const;
			
				

			bool IsGenerated();

			
			INT32 GetFrameBufferWidth() const;
			INT32 GetFrameBufferHeight() const;

			void ClearColorTexture(const UINT32 bindingPosition, const float r, const float g, const float b, const float a) const;
			void ClrearDepthTexture(const float depthValue) const;
			void ClrearStencilexture(const int stencilValue) const;
			void ClrearDepthStencilTexture(const float depthValue, const int stencilValue) const;

			std::unique_ptr<UINT8[]> ReadPixelsFromColorTexture
			(
				const UINT32 bindingPosition,
				const unsigned long long bufferSize,
				const int startX,
				const int startY,
				const int width,
				const int height,
				const GraphicsAPI::eTextureComponentFormat pixelFormat,
				const GraphicsAPI::eDataType dataType
			) const;
			//std::unique_ptr<UINT8[]> ReadPixelsFromDepthTexture() const;

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


