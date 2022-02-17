#pragma once

#include <Core.h>

#include <Asset/TextureAsset.h>

#include "FrameBufferView.reflection.h"
namespace dooms
{
	namespace graphics
	{
		/**
		 * \brief
		 * FrameBufferID in opengl.
		 * RenderTargetView, DepthStencilView in dx11
		 */
		class D_CLASS FrameBufferView : public DObject
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			asset::TextureAsset* mTextureResource;

			D_PROPERTY()
			BufferID mViewID;

			D_PROPERTY()
			INT32 mBindingPosition;

			D_PROPERTY()
			GraphicsAPI::eGraphicsPipeLineStage mGraphicsPipeLineStage;

		public:

			FrameBufferView();
			~FrameBufferView();

			FrameBufferView
			(
				asset::TextureAsset* const _textureResource,
				BufferID _renderTargetView,
				INT32 bindingPosition = -1,
				GraphicsAPI::eGraphicsPipeLineStage mGraphicsPipeLineStage = GraphicsAPI::eGraphicsPipeLineStage::DUMMY
			);

			FrameBufferView(const FrameBufferView&);
			FrameBufferView(FrameBufferView&&) noexcept;
			FrameBufferView& operator=(const FrameBufferView&);
			FrameBufferView& operator=(FrameBufferView&&) noexcept;

			bool IsValid() const;
			
			asset::TextureAsset* GetTextureResource() const;
			
			FORCE_INLINE INT32 GetBindingPosition() const
			{
				return mBindingPosition;
			}

			FORCE_INLINE GraphicsAPI::eGraphicsPipeLineStage GetGraphicsPipeLineStage() const
			{
				return mGraphicsPipeLineStage;
			}

			FORCE_INLINE BufferID GetViewID() const
			{
				return mViewID;
			}
		};
	}
}

