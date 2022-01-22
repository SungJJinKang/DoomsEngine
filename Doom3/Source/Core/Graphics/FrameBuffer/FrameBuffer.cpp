#include "FrameBuffer.h"

#include "Asset/TextureAsset.h"
#include <Math/LightMath_Cpp/Utility.h>

#include "Graphics/GraphicsAPI/graphicsAPISetting.h"

dooms::graphics::FrameBuffer::FrameBuffer()
	: mDefaultWidth{ 0 }, mDefaultHeight{ 0 }, mFrameBufferIDForOPENGL{}, mAttachedColorTextureViews{}, mAttachedDepthStencilTextureView{nullptr}
{
}

dooms::graphics::FrameBuffer::FrameBuffer(UINT32 defaultWidth, UINT32 defaultHeight)
	: mDefaultWidth{ defaultWidth }, mDefaultHeight{ defaultHeight }, mFrameBufferIDForOPENGL{}, mAttachedColorTextureViews{}, mAttachedDepthStencilTextureView{ nullptr }
{
}

void dooms::graphics::FrameBuffer::GenerateFrameBuffer()
{
	if(dooms::graphics::GraphicsAPI::GetCuurentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		mFrameBufferIDForOPENGL = GraphicsAPI::GenerateFrameBuffer();
	}
	
}

dooms::graphics::BufferID dooms::graphics::FrameBuffer::GetFrameBufferIDForOPENGL() const
{
	return mFrameBufferIDForOPENGL;
}

void dooms::graphics::FrameBuffer::StaticBindFrameBuffer(const FrameBuffer* const frameBuffer)
{
	if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(FRAMEBUFFER_TAG, (frameBuffer != nullptr) ? reinterpret_cast<UINT64>(frameBuffer) : 0))
	{
		FrameBuffer::PreviousFrameBuffer = CurrentFrameBuffer;
		if (frameBuffer == nullptr)
		{
			StaticBindBackFrameBuffer();
		}
		else
		{
			if(GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				UINT64 frameBufferID[1];
				frameBufferID[0] = frameBuffer->GetFrameBufferIDForOPENGL();

				dooms::graphics::GraphicsAPI::BindFrameBuffer(1, reinterpret_cast<unsigned long long* const*>(&frameBufferID), 0);
				GraphicsAPI::SetViewport(0, 0, 0, frameBuffer->mDefaultWidth, frameBuffer->mDefaultHeight);

				std::vector< GraphicsAPI::eBufferMode> drawBufferModes;
				drawBufferModes.reserve(10);
				for(dooms::graphics::FrameBufferView* frameBufferView : frameBuffer->mAttachedColorTextureViews)
				{
					drawBufferModes.emplace_back(GraphicsAPI::eBufferMode::COLOR_ATTACHMENT0 + frameBufferView->GetBindingPosition());
				}
				GraphicsAPI::SetDrawBuffers(drawBufferModes.size(), drawBufferModes.data());
				
			}
			else if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
			{
				unsigned long long renderTargetViewList[15];
				INT32 renderTargetViewCount = 0;
				for (FrameBufferView* renderTargetView : frameBuffer->mAttachedColorTextureViews)
				{
					assert(renderTargetView->GetBindingPosition() < 10);
					renderTargetViewList[renderTargetView->GetBindingPosition()] = renderTargetView->GetViewID();
					renderTargetViewCount = math::Max(renderTargetViewCount, renderTargetView->GetBindingPosition());
				}

				const unsigned long long depthStencilView = (IsValid(frameBuffer->mAttachedDepthStencilTextureView) && frameBuffer->mAttachedDepthStencilTextureView->IsValid()) ? frameBuffer->mAttachedDepthStencilTextureView->GetViewID().GetBufferID() : 0;

				dooms::graphics::GraphicsAPI::BindFrameBuffer(renderTargetViewCount, reinterpret_cast<unsigned long long* const*>(&renderTargetViewList), depthStencilView);
				GraphicsAPI::SetViewport(0, 0, 0, frameBuffer->mDefaultWidth, frameBuffer->mDefaultHeight);
			}
			else
			{
				D_ASSERT(0);
			}
	
		}
		FrameBuffer::CurrentFrameBuffer = frameBuffer;
	}
}

void dooms::graphics::FrameBuffer::StaticBindBackFrameBuffer()
{
	dooms::graphics::GraphicsAPI::BindBackBuffer();
	GraphicsAPI::SetViewport(0, 0, 0, graphics::graphicsAPISetting::GetScreenWidth(), graphics::graphicsAPISetting::GetScreenHeight());

}

void dooms::graphics::FrameBuffer::BindFrameBuffer() const noexcept
{
	D_ASSERT(mDefaultWidth != 0 && mDefaultHeight != 0);
	FrameBuffer::StaticBindFrameBuffer(this);
}

void dooms::graphics::FrameBuffer::RevertFrameBuffer()
{
	if (FrameBuffer::PreviousFrameBuffer != nullptr)
	{
		FrameBuffer::PreviousFrameBuffer->BindFrameBuffer();
	}
	else
	{
		FrameBuffer::StaticBindBackFrameBuffer(); // bind defualt screen buffer
	}
}


void dooms::graphics::FrameBuffer::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestoryFrameBufferObject();
}

void dooms::graphics::FrameBuffer::DestoryFrameBufferObject()
{
	if (mFrameBufferIDForOPENGL.IsValid())
	{
		GraphicsAPI::DestroyFrameBuffer(mFrameBufferIDForOPENGL);
		mFrameBufferIDForOPENGL.Reset();
	}
}

dooms::graphics::FrameBuffer::~FrameBuffer()
{
	DestoryFrameBufferObject();
}


bool dooms::graphics::FrameBuffer::IsGenerated()
{
	return mFrameBufferIDForOPENGL.IsValid();
}

INT32 dooms::graphics::FrameBuffer::GetFrameBufferWidth() const
{
	if (dooms::graphics::GraphicsAPI::GetCuurentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		return graphics::GraphicsAPI::GetFrameBufferWidth(mFrameBufferIDForOPENGL);
	}
	else
	{
		D_ASSERT(false);
		return 0;
	}
	
}

INT32 dooms::graphics::FrameBuffer::GetFrameBufferHeight() const
{
	if (dooms::graphics::GraphicsAPI::GetCuurentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		return graphics::GraphicsAPI::GetFrameBufferHeight(mFrameBufferIDForOPENGL);
	}
	else
	{
		D_ASSERT(false);
		return 0;
	}
}

/*
INT32 FrameBuffer::GetFrameBufferParameteriv(const eFrameBufferParameterPName frameBufferParameterPName) const
{
	return GetFrameBufferParameterivStatic(this, frameBufferParameterPName);
}

INT32 FrameBuffer::GetFrameBufferParameterivStatic
(
	const FrameBuffer* const frameBuffer,
	const eFrameBufferParameterPName frameBufferParameterPName
)
{
	D_ASSERT(frameBuffer != nullptr);
	frameBuffer->BindFrameBuffer();

	INT32 data;

	if (GraphicsAPI::GetGraphicsAPIType() == dooms::graphics::eGraphicsAPIType::OpenGL)
	{
		glGetFramebufferParameteriv(static_cast<UINT32>(GraphicsAPI::eBindFrameBufferTarget::FRAMEBUFFER), static_cast<UINT32>(frameBufferParameterPName), &data);
	}
	else
	{
		D_ASSERT(false);
	}

	return data;
}
*/

/*
void FrameBuffer::ClearFrameBuffer() const
{
	if( (mClearBit & GraphicsAPI::eBufferBitType::COLOR_BUFFER) != 0)
	{
		GraphicsAPI::ClearFrameBufferColorBuffer(mbu)
	}
	if ((mClearBit & GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER) != 0)
	{

	}
	else if ((mClearBit & GraphicsAPI::eBufferBitType::DEPTH_BUFFER) != 0)
	{

	}
}
*/

void dooms::graphics::FrameBuffer::BlitFrameBufferFromToFrameBuffer
(
	dooms::graphics::FrameBuffer* const fromFrameBuffer, dooms::graphics::FrameBuffer* const toFrameBuffer,
	INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1, 
	INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
	GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter
) noexcept
{
	//BackBuffer ID is zero!!
	//D_ASSERT(readFrameBuffer != INVALID_BUFFER_ID);
	//D_ASSERT(drawFrameBuffer != INVALID_BUFFER_ID);
	
	if (IsValid(toFrameBuffer) == true)
	{
		if (graphics::GraphicsAPI::GetCuurentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			GraphicsAPI::BlitFrameBuffer
			(
				(fromFrameBuffer == nullptr) ? 0 : fromFrameBuffer->GetFrameBufferIDForOPENGL().GetBufferID(),
				(toFrameBuffer == nullptr) ? 0 : toFrameBuffer->GetFrameBufferIDForOPENGL().GetBufferID(),
				srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,
				mask, filter
			);
		}
		else if (graphics::GraphicsAPI::GetCuurentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			switch (mask)
			{
			case GraphicsAPI::COLOR_BUFFER:

				D_ASSERT( > GetAttachedColorTextureCount() == toFrameBuffer->GetAttachedColorTextureCount())
					for (size_t colorTextureIndex = 0; colorTextureIndex < GetAttachedColorTextureCount(); colorTextureIndex++)
					{

					}
				break;

			case GraphicsAPI::DEPTH_BUFFER:
			case GraphicsAPI::STENCIL_BUFFER:
			case GraphicsAPI::DEPTH_STENCIL_BUFFER:

				asset::TextureAsset* const fromDepthStencilTextureResource = (fromFrameBuffer == nullptr) ? nullptr : fromFrameBuffer->GetDepthStencilTextureResourceObject();
				asset::TextureAsset* const toDepthStencilTextureResource = (toFrameBuffer == nullptr) ? nullptr : toFrameBuffer->GetDepthStencilTextureResourceObject();

				GraphicsAPI::BlitFrameBuffer
				(
					(IsValid(fromDepthStencilTextureResource) == true) ? 0 : fromDepthStencilTextureResource->GetTextureResourceObject().GetBufferID(),
					(IsValid(toDepthStencilTextureResource) == true) ? 0 : toDepthStencilTextureResource->GetTextureResourceObject().GetBufferID(),
					srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,
					mask, filter
				);
				break;

			default:
				D_ASSERT(false);
			}
		}
	}

}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::AttachColorTextureToFrameBuffer
(
	UINT32 bindingPosition,
	UINT32 width, 
	UINT32 height
)
{
	if (mFrameBufferIDForOPENGL.IsValid() == false)
	{
		GenerateFrameBuffer();
	}

	dooms::asset::TextureAsset* const colorTexture = dooms::CreateDObject<dooms::asset::TextureAsset>
	(
		GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
		GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8,
		GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE,
		width,
		height,
		GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA,
		GraphicsAPI::eDataType::FLOAT,
		(dooms::graphics::GraphicsAPI::eBindFlag)(dooms::graphics::GraphicsAPI::eBindFlag::BIND_RENDER_TARGET | dooms::graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE),
		dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D
	);
	const BufferID renderTargetViewObject = GraphicsAPI::Attach2DTextureToFrameBuffer
	(
		mFrameBufferIDForOPENGL,
		static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0 + bindingPosition),
		GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
		colorTexture->GetTextureResourceObject(),
		0
	);

	mAttachedColorTextureViews.emplace_back(dooms::CreateDObject<FrameBufferView>(colorTexture, renderTargetViewObject, bindingPosition));

	return colorTexture;
}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::AttachDepthTextureToFrameBuffer
(
	UINT32 width, 
	UINT32 height
)
{
	D_ASSERT_LOG( (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid()) == false, "A Depth Buffer is already attached");

	if (mFrameBufferIDForOPENGL.IsValid() == false)
	{
		GenerateFrameBuffer();
	}

	dooms::asset::TextureAsset* const depthTexture = dooms::CreateDObject<dooms::asset::TextureAsset>
	(
		GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
		GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8,
		GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE,
		width,
		height,
		GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_COMPONENT,
		GraphicsAPI::eDataType::FLOAT,
		(dooms::graphics::GraphicsAPI::eBindFlag)(dooms::graphics::GraphicsAPI::eBindFlag::BIND_DEPTH_STENCIL | dooms::graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE),
		dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D
	);
	const BufferID depthStencilView = GraphicsAPI::Attach2DTextureToFrameBuffer
	(
		mFrameBufferIDForOPENGL,
		static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT),
		GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
		depthTexture->GetTextureResourceObject(),
		0
	);

	mAttachedDepthStencilTextureView = dooms::CreateDObject<FrameBufferView>(depthTexture, depthStencilView, -1);
	return depthTexture;
}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::AttachDepthStencilTextureToFrameBuffer
(
	UINT32 width, 
	UINT32 height
)
{
	D_ASSERT_LOG(( IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid() ) == false, "A Depth Stencil Buffer is already attached");

	if (mFrameBufferIDForOPENGL.IsValid() == false)
	{
		GenerateFrameBuffer();
	}

	dooms::asset::TextureAsset* const depthStencilTexture = dooms::CreateDObject<dooms::asset::TextureAsset>
	(
		GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
		GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8,
		GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE,
		width,
		height,
		GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_STENCIL,
		GraphicsAPI::eDataType::UNSIGNED_INT_24_8,
		(dooms::graphics::GraphicsAPI::eBindFlag)(dooms::graphics::GraphicsAPI::eBindFlag::BIND_DEPTH_STENCIL | dooms::graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE),
		dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D
	);
	const BufferID depthStencilView = GraphicsAPI::Attach2DTextureToFrameBuffer
	(
		mFrameBufferIDForOPENGL,
		static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT),
		GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
		depthStencilTexture->GetTextureResourceObject(),
		0
	);

	mAttachedDepthStencilTextureView = dooms::CreateDObject<FrameBufferView>(depthStencilTexture, depthStencilView, -1);
	return depthStencilTexture;
}

size_t dooms::graphics::FrameBuffer::GetAttachedColorTextureCount()
{
	return mAttachedColorTextureViews.size();
}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::GetColorTextureResourceObject(const UINT32 bindingPosition) const
{
	dooms::asset::TextureAsset* colorTexture = nullptr;

	for (FrameBufferView* attachedColorTexture : mAttachedColorTextureViews)
	{
		D_ASSERT(IsValid(attachedColorTexture) && attachedColorTexture->IsValid());
		if (attachedColorTexture->GetBindingPosition() == bindingPosition)
		{
			colorTexture = attachedColorTexture->GetTextureResource();
			break;
		}
	}

	D_ASSERT(IsValid(colorTexture));
	return colorTexture;
}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::GetDepthTextureResourceObject() const
{
	if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
	{
		return mAttachedDepthStencilTextureView->GetTextureResource();
	}
	else
	{
		return nullptr;
	}
}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::GetDepthStencilTextureResourceObject() const
{
	if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
	{
		return mAttachedDepthStencilTextureView->GetTextureResource();
	}
	else
	{
		return nullptr;
	}
}

dooms::graphics::FrameBufferView* dooms::graphics::FrameBuffer::GetColorTextureRenderTargetView(const UINT32 bindingPosition) const
{
	dooms::graphics::FrameBufferView* frameBufferRenderTargetView = nullptr;
	for (dooms::graphics::FrameBufferView* attachedColorTexture : mAttachedColorTextureViews)
	{
		D_ASSERT(IsValid(attachedColorTexture) && attachedColorTexture->IsValid());
		if (attachedColorTexture->GetBindingPosition() == bindingPosition)
		{
			frameBufferRenderTargetView = attachedColorTexture;
			break;
		}
	}

	D_ASSERT(IsValid(frameBufferRenderTargetView));
	return frameBufferRenderTargetView;
}

dooms::graphics::FrameBufferView* dooms::graphics::FrameBuffer::GetDepthTextureRenderTargetView() const
{
	if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
	{
		return mAttachedDepthStencilTextureView;
	}
	else
	{
		return nullptr;
	}
}

dooms::graphics::FrameBufferView* dooms::graphics::FrameBuffer::GetDepthStencilTextureRenderTargetView() const
{
	if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
	{
		return mAttachedDepthStencilTextureView;
	}
	else
	{
		return nullptr;
	}
}

dooms::graphics::TextureView* dooms::graphics::FrameBuffer::GetColorTextureView
(
	const UINT32 bindingPosition,
	const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
) const
{
	return dooms::CreateDObject<dooms::graphics::TextureView>(GetColorTextureResourceObject(bindingPosition), bindingPosition, defaultTargetGraphicsPipeLineStage);
}

dooms::graphics::TextureView* dooms::graphics::FrameBuffer::GetDepthTextureView
(
	const UINT32 bindingPosition,
	const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
) const
{
	return dooms::CreateDObject<dooms::graphics::TextureView>(GetDepthTextureResourceObject(), bindingPosition, defaultTargetGraphicsPipeLineStage);
}

dooms::graphics::TextureView* dooms::graphics::FrameBuffer::GetDepthStencilTextureView
(
	const UINT32 bindingPosition,
	const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
) const
{
	return dooms::CreateDObject<dooms::graphics::TextureView>(GetDepthStencilTextureResourceObject(), bindingPosition, defaultTargetGraphicsPipeLineStage);
}


void dooms::graphics::FrameBuffer::ClearColorTexture
(
	const UINT32 bindingPosition,
	const float r,
	const float g,
	const float b,
	const float a
) const
{
	if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		GraphicsAPI::ClearFrameBufferColorBuffer(mFrameBufferIDForOPENGL, r, g, b, a);
	}
	else if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		dooms::asset::TextureAsset* const colorTexture = GetColorTextureResourceObject(bindingPosition);
		D_ASSERT(IsValid(colorTexture) == true);
		if (IsValid(colorTexture) == true)
		{

		}
	}

}

void dooms::graphics::FrameBuffer::ClrearDepthTexture(const float depthValue) const
{
	if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(mFrameBufferIDForOPENGL.IsValid());
		if (mFrameBufferIDForOPENGL.IsValid())
		{
			GraphicsAPI::ClearFrameBufferDepthBuffer(mFrameBufferIDForOPENGL, depthValue);
		}
	}
	else if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		D_ASSERT(IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid());
		if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
		{
			GraphicsAPI::ClearFrameBufferDepthBuffer(mAttachedDepthStencilTextureView->GetViewID(), depthValue);
		}
	}
}

void dooms::graphics::FrameBuffer::ClrearStencilexture(const int stencilValue) const
{
	if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(mFrameBufferIDForOPENGL.IsValid());
		if (mFrameBufferIDForOPENGL.IsValid())
		{
			GraphicsAPI::ClearFrameBufferStencilBuffer(mFrameBufferIDForOPENGL, stencilValue);
		}
	}
	else if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		D_ASSERT(IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid());
		if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
		{
			GraphicsAPI::ClearFrameBufferStencilBuffer(mAttachedDepthStencilTextureView->GetViewID(), stencilValue);
		}
	}
}

void dooms::graphics::FrameBuffer::ClrearDepthStencilTexture(const float depthValue, const int stencilValue) const
{
	if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(mFrameBufferIDForOPENGL.IsValid());
		if (mFrameBufferIDForOPENGL.IsValid())
		{
			GraphicsAPI::ClearFrameBufferDepthStencilBuffer(mFrameBufferIDForOPENGL, depthValue, stencilValue);
		}
	}
	else if (GraphicsAPI::GetCuurentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		D_ASSERT(IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid());
		if (IsValid(mAttachedDepthStencilTextureView) && mAttachedDepthStencilTextureView->IsValid())
		{
			GraphicsAPI::ClearFrameBufferDepthStencilBuffer(mAttachedDepthStencilTextureView->GetViewID(), depthValue, stencilValue);
		}
	}
}


/*
RenderBuffer& FrameBuffer::AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType, UINT32 width, UINT32 height)
{
	D_ASSERT(mFrameBufferIDForOPENGL.IsValid());

	auto& createdRenderBuffer = mAttachedRenderBuffers.emplace_back(*this, renderBufferType, width, height);
	mClearBit |= static_cast<UINT32>(renderBufferType);

	CheckIsFrameBufferSuccesfullyCreated();
	return createdRenderBuffer;
}

RenderBuffer& dooms::graphics::FrameBuffer::AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType)
{
	return AttachRenderBuffer(renderBufferType, mDefaultWidth, mDefaultHeight);
}
*/

