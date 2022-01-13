#include "FrameBuffer.h"

using namespace dooms::graphics;


dooms::graphics::FrameBuffer::FrameBuffer()
	: mDefaultWidth{ 0 }, mDefaultHeight{ 0 }, mClearBit{ 0 }, mFrameBufferID()
{
}

FrameBuffer::FrameBuffer(UINT32 defaultWidth, UINT32 defaultHeight)
	: mDefaultWidth{ defaultWidth }, mDefaultHeight{ defaultHeight }, mClearBit{ 0 }, mFrameBufferID()
{
	mAttachedRenderBuffers.reserve(RESERVED_RENDERBUFFER_COUNT);
	mAttachedColorTextures.reserve(RESERVED_COLOR_TEXTURE_COUNT);
	mAttachedDepthTextures.reserve(RESERVED_DEPTH_TEXTURE_COUNT);
	mAttachedDepthStencilTextures.reserve(RESERVED_DEPTH_STENCIL_TEXTURE_COUNT);
}

void dooms::graphics::FrameBuffer::GenerateBuffer(UINT32 defaultWidth, UINT32 defaultHeight)
{
	D_ASSERT(defaultWidth != 0 && defaultHeight != 0);

	mDefaultWidth = defaultWidth;
	mDefaultHeight = defaultHeight;
	mFrameBufferID = GraphicsAPI::GenerateFrameBuffer();
}


void FrameBuffer::RefreshTargetDrawBufferContainer()
{
	mTargetDrawBufferContainer.clear();
	mTargetDrawBufferContainer.reserve(mAttachedColorTextures.size());

	for (UINT32 i = 0; i < mAttachedColorTextures.size(); i++)
	{
		mTargetDrawBufferContainer.emplace_back(static_cast<GraphicsAPI::eBufferMode>(GraphicsAPI::eBufferMode::COLOR_ATTACHMENT0 + i));
	}
}

void FrameBuffer::SetTargetDrawBuffer()
{
	GraphicsAPI::SetDrawBuffers(static_cast<INT32>(mTargetDrawBufferContainer.size()), mTargetDrawBufferContainer.data());
}


void FrameBuffer::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestoryFrameBufferObject();
}

void FrameBuffer::DestoryFrameBufferObject()
{
	if (mFrameBufferID.IsValid())
	{
		GraphicsAPI::DestroyFrameBuffer(mFrameBufferID);
		mFrameBufferID.Reset();
	}
}

FrameBuffer::~FrameBuffer()
{
	DestoryFrameBufferObject();
}

FrameBuffer::FrameBuffer(const FrameBuffer& frameBuffer)
	:	mFrameBufferID(),
		mDefaultWidth(frameBuffer.mDefaultWidth),
		mDefaultHeight(frameBuffer.mDefaultHeight),
		mClearBit(0),
		mDrawTarget(0)
{
	//Never Copy This!!
	//std::vector<RenderBuffer> mAttachedRenderBuffers;
	//std::vector<SingleTexture> mAttachedColorTextures;
	//std::vector<SingleTexture> mAttachedDepthTextures;
	//std::vector<SingleTexture> mAttachedDepthStencilTextures;
	//std::vector<UINT32> mTargetDrawBufferContainer;

	if(frameBuffer.mFrameBufferID.IsValid() == true)
	{
		GenerateBuffer(mDefaultWidth, mDefaultHeight);

		for (const RenderBuffer& renderBuffer : frameBuffer.mAttachedRenderBuffers)
		{
			AttachRenderBuffer(renderBuffer.GetFrameBufferType(), renderBuffer.GetWidth(), renderBuffer.GetHeight());
		}

		for (const SingleTexture& attachedTexture : frameBuffer.mAttachedColorTextures)
		{
			AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER, attachedTexture.GetWidth(), attachedTexture.GetHeight());
		}

		for (const SingleTexture& attachedTexture : frameBuffer.mAttachedDepthTextures)
		{
			AttachTextureBuffer(GraphicsAPI::eBufferBitType::DEPTH_BUFFER, attachedTexture.GetWidth(), attachedTexture.GetHeight());
		}

		for (const SingleTexture& attachedTexture : frameBuffer.mAttachedDepthStencilTextures)
		{
			AttachTextureBuffer(GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER, attachedTexture.GetWidth(), attachedTexture.GetHeight());
		}

		RefreshTargetDrawBufferContainer();
	}

	
}


void FrameBuffer::CheckIsFrameBufferSuccesfullyCreated() noexcept
{
	BindFrameBuffer();
	const unsigned int errorCode = GraphicsAPI::CheckFrameBufferIsSuccesfullyCreated();
	D_ASSERT_LOG(errorCode == 0, "fail frame buffer : %u", errorCode);
}

const dooms::graphics::SingleTexture* FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index) const
{
	const dooms::graphics::SingleTexture* targetTexture = nullptr;
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR_BUFFER:
		D_ASSERT(index >= 0 && index < mAttachedColorTextures.size());
		if (index >= 0 && index < mAttachedColorTextures.size())
		{
			targetTexture = &mAttachedColorTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_BUFFER:
		D_ASSERT(index >= 0 && index < mAttachedDepthTextures.size());
		if (index >= 0 && index < mAttachedDepthTextures.size())
		{
			targetTexture = &mAttachedDepthTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER:
		D_ASSERT(index >= 0 && index < mAttachedDepthStencilTextures.size());
		if (index >= 0 && index < mAttachedDepthStencilTextures.size())
		{
			targetTexture = &mAttachedDepthStencilTextures[index];
		}
		break;

	default:
		NEVER_HAPPEN;
	}

	return targetTexture;
}

dooms::graphics::SingleTexture* FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index)
{
	dooms::graphics::SingleTexture* targetTexture = nullptr;
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR_BUFFER:
		D_ASSERT(index >= 0 && index < mAttachedColorTextures.size());
		if (index >= 0 && index < mAttachedColorTextures.size())
		{
			targetTexture = &mAttachedColorTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_BUFFER:
		D_ASSERT(index >= 0 && index < mAttachedDepthTextures.size());
		if (index >= 0 && index < mAttachedDepthTextures.size())
		{
			targetTexture = &mAttachedDepthTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER:
		D_ASSERT(index >= 0 && index < mAttachedDepthStencilTextures.size());
		if (index >= 0 && index < mAttachedDepthStencilTextures.size())
		{
			targetTexture = &mAttachedDepthStencilTextures[index];
		}
		break;

	default:
		NEVER_HAPPEN;
	}

	return targetTexture;
}

bool dooms::graphics::FrameBuffer::IsGenerated()
{
	return mFrameBufferID.IsValid();
}

INT32 FrameBuffer::GetFrameBufferWidth() const
{
	return graphics::GraphicsAPI::GetFrameBufferWidth(mFrameBufferID);
}

INT32 FrameBuffer::GetFrameBufferHeight() const
{
	return graphics::GraphicsAPI::GetFrameBufferHeight(mFrameBufferID);
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

void FrameBuffer::BlitFrameBufferTo(
	UINT32 ReadFrameBufferId, UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0,
	INT32 srcX1, INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
	GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter
) noexcept
{
	//BackBuffer ID is zero!!
	//D_ASSERT(ReadFrameBufferId != INVALID_BUFFER_ID);
	//D_ASSERT(DrawFrameBufferId != INVALID_BUFFER_ID);

	GraphicsAPI::BlitFrameBuffer(ReadFrameBufferId, DrawFrameBufferId, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}


void FrameBuffer::BlitFrameBufferTo(
	UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1,
	INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, GraphicsAPI::eBufferBitType mask,
	GraphicsAPI::eImageInterpolation filter
) const noexcept
{
	//BackBuffer ID is zero!!
	D_ASSERT(mFrameBufferID.IsValid());
	//D_ASSERT(DrawFrameBufferId != INVALID_BUFFER_ID);
	
	GraphicsAPI::BlitFrameBuffer(mFrameBufferID, DrawFrameBufferId, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}


void FrameBuffer::BlitFrameBufferFrom(
	UINT32 ReadFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1,
	INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, GraphicsAPI::eBufferBitType mask,
	GraphicsAPI::eImageInterpolation filter
) const noexcept
{
	//BackBuffer ID is zero!!
	//D_ASSERT(ReadFrameBufferId != INVALID_BUFFER_ID);
	D_ASSERT(mFrameBufferID.IsValid());

	GraphicsAPI::BlitFrameBuffer(ReadFrameBufferId, mFrameBufferID, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void FrameBuffer::BlitFrameBufferToTexture(
	dooms::graphics::Texture* const drawTexture, INT32 srcX0, INT32 srcY0,
	INT32 srcX1, INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
	GraphicsAPI::eBufferBitType mask, GraphicsAPI::eImageInterpolation filter
) const noexcept
{
	D_ASSERT(drawTexture != nullptr);
	
	GraphicsAPI::BlitFrameBuffer(mFrameBufferID, drawTexture->GetTextureBufferID(), srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

RenderBuffer& FrameBuffer::AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType, UINT32 width, UINT32 height)
{
	D_ASSERT(mFrameBufferID.IsValid());

	auto& createdRenderBuffer = mAttachedRenderBuffers.emplace_back(*this, renderBufferType, width, height);
	mClearBit |= static_cast<UINT32>(renderBufferType);

	CheckIsFrameBufferSuccesfullyCreated();
	return createdRenderBuffer;
}

RenderBuffer& dooms::graphics::FrameBuffer::AttachRenderBuffer(GraphicsAPI::eFrameBufferAttachmentPoint renderBufferType)
{
	return AttachRenderBuffer(renderBufferType, mDefaultWidth, mDefaultHeight);
}

SingleTexture& FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height)
{
	D_ASSERT(mFrameBufferID.IsValid());

	BindFrameBuffer();

	dooms::graphics::SingleTexture* createdTexture = nullptr;
	
	switch (frameBufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR_BUFFER:
	{
		SingleTexture colorTexture{ GraphicsAPI::eTextureType::DIFFUSE, GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
			GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA8, width, height, GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA, GraphicsAPI::eDataType::FLOAT, NULL };
		GraphicsAPI::Attach2DTextureToFrameBuffer(GraphicsAPI::eBindFrameBufferTarget::FRAMEBUFFER, static_cast<GraphicsAPI::eFrameBufferAttachmentPoint>(GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0 + static_cast<UINT32>(mAttachedColorTextures.size())), GraphicsAPI::eTextureBindTarget::TEXTURE_2D, colorTexture.GetTextureBufferID(), 0);

		mClearBit |= static_cast<UINT32>(GraphicsAPI::eBufferBitType::COLOR_BUFFER);
		mDrawTarget |= GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0 + mAttachedColorTextures.size();

		createdTexture = &mAttachedColorTextures.emplace_back(std::move(colorTexture));

		RefreshTargetDrawBufferContainer();
		SetTargetDrawBuffer();
		
		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH_BUFFER:
	{
		D_ASSERT(mAttachedDepthTextures.size() == 0);

		SingleTexture depthTexture{ GraphicsAPI::eTextureType::DIFFUSE, GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
			GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32, width, height, GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_COMPONENT, GraphicsAPI::eDataType::FLOAT, NULL };
		GraphicsAPI::Attach2DTextureToFrameBuffer(GraphicsAPI::eBindFrameBufferTarget::FRAMEBUFFER, GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT, GraphicsAPI::eTextureBindTarget::TEXTURE_2D, depthTexture.GetTextureBufferID(), 0);


		mAttachedDepthTextures.push_back(std::move(depthTexture));
		createdTexture = &mAttachedDepthTextures.back();

		mClearBit |= static_cast<UINT32>(GraphicsAPI::eBufferBitType::DEPTH_BUFFER);

		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER:
	{
		D_ASSERT(mAttachedDepthStencilTextures.size() == 0);

		SingleTexture depthStencilTexture{ GraphicsAPI::eTextureType::DIFFUSE, GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D,
			GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8, width, height, GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_STENCIL, GraphicsAPI::eDataType::UNSIGNED_INT_24_8, NULL };
		GraphicsAPI::Attach2DTextureToFrameBuffer(GraphicsAPI::eBindFrameBufferTarget::FRAMEBUFFER, GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT, GraphicsAPI::eTextureBindTarget::TEXTURE_2D, depthStencilTexture.GetTextureBufferID(), 0);

		mAttachedDepthStencilTextures.push_back(std::move(depthStencilTexture));
		createdTexture = &mAttachedDepthStencilTextures.back();

		mClearBit |= static_cast<UINT32>(GraphicsAPI::eBufferBitType::DEPTH_STENCIL_BUFFER);
		break;

	}
		
	default:
		NEVER_HAPPEN;
		break;

	}
	
	return *createdTexture;
}

SingleTexture& dooms::graphics::FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType)
{
	return AttachTextureBuffer(frameBufferType, mDefaultWidth, mDefaultHeight);
}



		
		
