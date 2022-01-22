#include "FrameBuffer.h"

#include "Asset/TextureAsset.h"
#include <Math/LightMath_Cpp/Utility.h>

dooms::graphics::FrameBuffer::FrameBuffer()
	: mDefaultWidth{ 0 }, mDefaultHeight{ 0 }, mFrameBufferIDForOPENGL{}, mAttachedColorTextures{}, mAttachedDepthStencilTexture{}
{
}

dooms::graphics::FrameBuffer::FrameBuffer(UINT32 defaultWidth, UINT32 defaultHeight)
	: mDefaultWidth{ defaultWidth }, mDefaultHeight{ defaultHeight }, mFrameBufferIDForOPENGL{}, mAttachedColorTextures{}, mAttachedDepthStencilTexture{}
{
}

void dooms::graphics::FrameBuffer::GenerateBuffer()
{
	if(dooms::graphics::GraphicsAPI::GetCuurentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		mFrameBufferIDForOPENGL = GraphicsAPI::GenerateFrameBuffer();
	}
	
}

void dooms::graphics::FrameBuffer::StaticBindFrameBuffer(const FrameBuffer* const frameBuffer)
{
	if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(FRAMEBUFFER_TAG, (frameBuffer != nullptr) ? reinterpret_cast<UINT64>(frameBuffer) : 0))
	{
		FrameBuffer::PreviousFrameBuffer = CurrentFrameBuffer;
		if (frameBuffer == nullptr)
		{
			dooms::graphics::GraphicsAPI::BindBackBuffer();
			GraphicsAPI::SetViewport(0, 0, 0, graphics::graphicsAPISetting::GetScreenWidth(), graphics::graphicsAPISetting::GetScreenHeight());
		}
		else
		{
			unsigned long long renderTargetViewList[15];
			INT32 renderTargetViewCount = 0;
			for(auto& renderTargetView : frameBuffer->mAttachedColorTextures)
			{
				assert(renderTargetView.mBindingPosition < 10);
				renderTargetViewList[renderTargetView.mBindingPosition] = renderTargetView.mRenderTargetView;
				renderTargetViewCount = math::Max(renderTargetViewCount, renderTargetView.mBindingPosition);
			}

			const unsigned long long depthStencilView = (frameBuffer->mAttachedDepthStencilTexture.IsValid() == true) ? frameBuffer->mAttachedDepthStencilTexture.mRenderTargetView.GetBufferID() : 0;

			dooms::graphics::GraphicsAPI::BindFrameBuffer(renderTargetViewCount, reinterpret_cast<unsigned long long* const*>(&renderTargetViewList), depthStencilView);
			GraphicsAPI::SetViewport(0, 0, 0, frameBuffer->mDefaultWidth, frameBuffer->mDefaultHeight);
		}
		FrameBuffer::CurrentFrameBuffer = frameBuffer;
	}
}

void dooms::graphics::FrameBuffer::BindFrameBuffer() const noexcept
{
	D_ASSERT(mDefaultWidth != 0 && mDefaultHeight != 0);
	FrameBuffer::StaticBindFrameBuffer(this);
}

void dooms::graphics::FrameBuffer::UnBindFrameBuffer() noexcept
{
	FrameBuffer::StaticBindFrameBuffer(nullptr); // bind MainFrameBuffer
}

void dooms::graphics::FrameBuffer::RevertFrameBuffer()
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



const dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, INT32 bindingPosition) const
{
	const dooms::asset::TextureAsset* targetTexture = nullptr;
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR_BUFFER:
		for (auto& colorTexture : mAttachedColorTextures)
		{
			if (colorTexture.mBindingPosition == bindingPosition)
			{
				targetTexture = colorTexture.mTextureResource;
				break;
			}
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_BUFFER:
	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER:
		targetTexture = mAttachedDepthStencilTexture.mTextureResource;
		break;

	default:
		NEVER_HAPPEN;
	}

	D_ASSERT(targetTexture != nullptr);

	return targetTexture;
}

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, INT32 bindingPosition)
{
	dooms::asset::TextureAsset* targetTexture = nullptr;
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR_BUFFER:
		for (auto& colorTexture : mAttachedColorTextures)
		{
			if (colorTexture.mBindingPosition == bindingPosition)
			{
				targetTexture = colorTexture.mTextureResource;
				break;
			}
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_BUFFER:
	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER:
		targetTexture = mAttachedDepthStencilTexture.mTextureResource;
		break;

	default:
		NEVER_HAPPEN;
	}

	D_ASSERT(targetTexture != nullptr);

	return targetTexture;
}

bool dooms::graphics::FrameBuffer::IsGenerated()
{
	return mFrameBufferIDForOPENGL.IsValid();
}

INT32 dooms::graphics::FrameBuffer::GetFrameBufferWidth() const
{
	return graphics::GraphicsAPI::GetFrameBufferWidth(mFrameBufferIDForOPENGL);
}

INT32 dooms::graphics::FrameBuffer::GetFrameBufferHeight() const
{
	return graphics::GraphicsAPI::GetFrameBufferHeight(mFrameBufferIDForOPENGL);
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
		GraphicsAPI::ClearBufferColorBuffer(mbu)
	}
	if ((mClearBit & GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER) != 0)
	{

	}
	else if ((mClearBit & GraphicsAPI::eBufferBitType::DEPTH_BUFFER) != 0)
	{

	}
}
*/

void dooms::graphics::FrameBuffer::BlitFrameBufferTo
(
	dooms::asset::TextureAsset* const readFrameBuffer, dooms::asset::TextureAsset* const drawFrameBuffer, 
	INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1, 
	INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
	GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter
) noexcept
{
	//BackBuffer ID is zero!!
	//D_ASSERT(readFrameBuffer != INVALID_BUFFER_ID);
	//D_ASSERT(drawFrameBuffer != INVALID_BUFFER_ID);

	GraphicsAPI::BlitFrameBuffer
	(
		(readFrameBuffer == nullptr) ? 0 : readFrameBuffer->GetTextureResourceObject().GetBufferID(),
		(drawFrameBuffer == nullptr) ? 0 : drawFrameBuffer->GetTextureResourceObject().GetBufferID(),
		srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,
		mask, filter
	);
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

dooms::asset::TextureAsset* dooms::graphics::FrameBuffer::AttachTextureBuffer
(
	GraphicsAPI::eBufferBitType frameBufferType,
	UINT32 bindingPosition, 
	UINT32 width,
	UINT32 height
)
{
	dooms::asset::TextureAsset* createdTexture = nullptr;
	
	switch (frameBufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR_BUFFER:
	{
		dooms::asset::TextureAsset* const colorTexture = dooms::CreateDObject<dooms::asset::TextureAsset>
		(
			GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
			GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8,
			GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE,
			width,
			height,
			GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA,
			GraphicsAPI::eDataType::FLOAT,
			(dooms::graphics::GraphicsAPI::eBindFlag)(dooms::graphics::GraphicsAPI::eBindFlag::BIND_RENDER_TARGET | dooms::graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE)
		);
		const BufferID renderTargetViewObject = GraphicsAPI::Attach2DTextureToFrameBuffer
		(
			mFrameBufferIDForOPENGL,
			static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0 + bindingPosition),
			GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
			colorTexture->GetTextureResourceObject()
		);
		
		mAttachedColorTextures.emplace_back(colorTexture, renderTargetViewObject, bindingPosition);
		createdTexture = colorTexture;

		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH_BUFFER:
	{
		D_ASSERT_LOG(mAttachedDepthStencilTexture.IsValid() == false, "A Depth Buffer is already attached");

		dooms::asset::TextureAsset* const depthTexture = dooms::CreateDObject<dooms::asset::TextureAsset>
		(
			GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
			GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8,
			GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE,
			width,
			height,
			GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_COMPONENT,
			GraphicsAPI::eDataType::FLOAT,
			(dooms::graphics::GraphicsAPI::eBindFlag)(dooms::graphics::GraphicsAPI::eBindFlag::BIND_DEPTH_STENCIL | dooms::graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE)
		);
		const BufferID depthStencilView = GraphicsAPI::Attach2DTextureToFrameBuffer
		(
			mFrameBufferIDForOPENGL,
			static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT),
			GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
			depthTexture->GetTextureResourceObject()
		);

		mAttachedDepthStencilTexture = FrameBufferTextureAndRenderTargetView{ depthTexture, depthStencilView, -1 };
		createdTexture = depthTexture;

		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER:
	{
		D_ASSERT_LOG(mAttachedDepthStencilTexture.IsValid() == false, "A Depth Stencil Buffer is already attached");

		dooms::asset::TextureAsset* const depthStencilTexture = dooms::CreateDObject<dooms::asset::TextureAsset>
		(
			GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
			GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8,
			GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE,
			width,
			height,
			GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_STENCIL,
			GraphicsAPI::eDataType::UNSIGNED_INT_24_8,
			(dooms::graphics::GraphicsAPI::eBindFlag)(dooms::graphics::GraphicsAPI::eBindFlag::BIND_DEPTH_STENCIL | dooms::graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE)
		);
		const BufferID depthStencilView = GraphicsAPI::Attach2DTextureToFrameBuffer
		(
			mFrameBufferIDForOPENGL,
			static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT),
			GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
			depthStencilTexture->GetTextureResourceObject()
		);


		mAttachedDepthStencilTexture = FrameBufferTextureAndRenderTargetView{ depthStencilTexture, depthStencilView, -1 };
		createdTexture = depthStencilTexture;

		break;

	}
		
	default:
		NEVER_HAPPEN;
		break;

	}

	return createdTexture;
	
}