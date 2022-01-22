#include "FrameBufferView.h"


dooms::graphics::FrameBufferView::FrameBufferView()
	: mTextureResource(nullptr), mViewID(), mBindingPosition(-1)
{

}

dooms::graphics::FrameBufferView::~FrameBufferView()
{
	if (mViewID.IsValid() == true)
	{
		GraphicsAPI::DestroyTextureViewObject(mViewID);
	}
}

dooms::graphics::FrameBufferView::FrameBufferView
(
	asset::TextureAsset* const _textureResource,
	BufferID _renderTargetView,
	INT32 bindingPosition,
	GraphicsAPI::eGraphicsPipeLineStage graphicsPipeLineStage
)
	: mTextureResource(_textureResource), mViewID(_renderTargetView), mBindingPosition(bindingPosition), mGraphicsPipeLineStage(graphicsPipeLineStage)
{
	D_ASSERT(_textureResource != nullptr);
	D_ASSERT(_renderTargetView.IsValid());
}

dooms::graphics::FrameBufferView::FrameBufferView(const FrameBufferView& frameBufferTextureAndRenderTargetView)
	: mTextureResource(frameBufferTextureAndRenderTargetView.mTextureResource), mBindingPosition(frameBufferTextureAndRenderTargetView.mBindingPosition), mGraphicsPipeLineStage(frameBufferTextureAndRenderTargetView.mGraphicsPipeLineStage)
{
	mViewID = frameBufferTextureAndRenderTargetView.mViewID.IsValid() ? graphics::GraphicsAPI::CopyRenderTargetView(frameBufferTextureAndRenderTargetView.mViewID) : BufferID::INVALID_BUFFER_ID;
}

dooms::graphics::FrameBufferView::FrameBufferView(FrameBufferView&& frameBufferTextureAndRenderTargetView) noexcept
	: mTextureResource(frameBufferTextureAndRenderTargetView.mTextureResource), mViewID(std::move(frameBufferTextureAndRenderTargetView.mViewID)), mBindingPosition(frameBufferTextureAndRenderTargetView.mBindingPosition), mGraphicsPipeLineStage(frameBufferTextureAndRenderTargetView.mGraphicsPipeLineStage)
{
	frameBufferTextureAndRenderTargetView.mTextureResource = nullptr;
}

dooms::graphics::FrameBufferView& dooms::graphics::FrameBufferView::operator=(const FrameBufferView& frameBufferTextureAndRenderTargetView)
{
	mTextureResource = frameBufferTextureAndRenderTargetView.mTextureResource;
	mViewID = frameBufferTextureAndRenderTargetView.mViewID.IsValid() ? graphics::GraphicsAPI::CopyRenderTargetView(frameBufferTextureAndRenderTargetView.mViewID) : BufferID::INVALID_BUFFER_ID;
	mBindingPosition = frameBufferTextureAndRenderTargetView.mBindingPosition;
	mGraphicsPipeLineStage = frameBufferTextureAndRenderTargetView.mGraphicsPipeLineStage;

	return *this;
}

dooms::graphics::FrameBufferView& dooms::graphics::FrameBufferView::operator=(FrameBufferView&& frameBufferTextureAndRenderTargetView) noexcept
{
	mTextureResource = frameBufferTextureAndRenderTargetView.mTextureResource;
	frameBufferTextureAndRenderTargetView.mTextureResource = nullptr;

	mViewID = std::move(frameBufferTextureAndRenderTargetView.mViewID);
	mBindingPosition = frameBufferTextureAndRenderTargetView.mBindingPosition;
	mGraphicsPipeLineStage = frameBufferTextureAndRenderTargetView.mGraphicsPipeLineStage;

	return *this;
}

bool dooms::graphics::FrameBufferView::IsValid() const
{
	return (mTextureResource != nullptr);
}

dooms::asset::TextureAsset* dooms::graphics::FrameBufferView::GetTextureResource() const
{
	return mTextureResource;
}
