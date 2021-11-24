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
	glGenFramebuffers(1, &(mFrameBufferID));
}


void FrameBuffer::RefreshTargetDrawBufferContainer()
{
	mTargetDrawBufferContainer.clear();
	mTargetDrawBufferContainer.reserve(mAttachedColorTextures.size());

	for (UINT32 i = 0; i < mAttachedColorTextures.size(); i++)
	{
		mTargetDrawBufferContainer.emplace_back(GL_COLOR_ATTACHMENT0 + i);
	}
}

void FrameBuffer::SetTargetDrawBuffer()
{
	glDrawBuffers(static_cast<INT32>(mTargetDrawBufferContainer.size()), mTargetDrawBufferContainer.data());
}


void FrameBuffer::DestoryFrameBufferObject()
{
	if (mFrameBufferID.IsValid())
	{
		glDeleteFramebuffers(1, &(mFrameBufferID));
		mFrameBufferID = 0;
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
			AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR, attachedTexture.GetWidth(), attachedTexture.GetHeight());
		}

		for (const SingleTexture& attachedTexture : frameBuffer.mAttachedDepthTextures)
		{
			AttachTextureBuffer(GraphicsAPI::eBufferBitType::DEPTH, attachedTexture.GetWidth(), attachedTexture.GetHeight());
		}

		for (const SingleTexture& attachedTexture : frameBuffer.mAttachedDepthStencilTextures)
		{
			AttachTextureBuffer(GraphicsAPI::eBufferBitType::DEPTH_STENCIL, attachedTexture.GetWidth(), attachedTexture.GetHeight());
		}

		RefreshTargetDrawBufferContainer();
	}

	
}


void FrameBuffer::CheckIsFrameBufferSuccesfullyCreated() noexcept
{
	BindFrameBuffer();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{//Fail Creating FrameBuffer
		D_ASSERT(false);
		D_DEBUG_LOG(logger::eLogType::D_ERROR, "fail frame buffer : %u", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}
}

const dooms::graphics::SingleTexture* FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index) const
{
	const dooms::graphics::SingleTexture* targetTexture = nullptr;
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR:
		D_ASSERT(index >= 0 && index < mAttachedColorTextures.size());
		if (index >= 0 && index < mAttachedColorTextures.size())
		{
			targetTexture = &mAttachedColorTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH:
		D_ASSERT(index >= 0 && index < mAttachedDepthTextures.size());
		if (index >= 0 && index < mAttachedDepthTextures.size())
		{
			targetTexture = &mAttachedDepthTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
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
	case GraphicsAPI::eBufferBitType::COLOR:
		D_ASSERT(index >= 0 && index < mAttachedColorTextures.size());
		if (index >= 0 && index < mAttachedColorTextures.size())
		{
			targetTexture = &mAttachedColorTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH:
		D_ASSERT(index >= 0 && index < mAttachedDepthTextures.size());
		if (index >= 0 && index < mAttachedDepthTextures.size())
		{
			targetTexture = &mAttachedDepthTextures[index];
		}
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
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
	glGetFramebufferParameteriv(static_cast<UINT32>(eBindFrameBufferTarget::FRAMEBUFFER), static_cast<UINT32>(frameBufferParameterPName), &data);

	return data;
}

void FrameBuffer::BlitFrameBufferTo(
	UINT32 ReadFrameBufferId, UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0,
	INT32 srcX1, INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
	GraphicsAPI::eBufferBitType mask, eImageInterpolation filter
) noexcept
{
	//BackBuffer ID is zero!!
	//D_ASSERT(ReadFrameBufferId != INVALID_BUFFER_ID);
	//D_ASSERT(DrawFrameBufferId != INVALID_BUFFER_ID);
	
	BindFrameBufferStatic(eBindFrameBufferTarget::READ_FRAMEBUFFER, ReadFrameBufferId);
	BindFrameBufferStatic(eBindFrameBufferTarget::DRAW_FRAMEBUFFER, DrawFrameBufferId);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<UINT32>(mask), static_cast<UINT32>(filter));
}


void FrameBuffer::BlitFrameBufferTo(
	UINT32 DrawFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1,
	INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, GraphicsAPI::eBufferBitType mask,
	eImageInterpolation filter
) const noexcept
{
	//BackBuffer ID is zero!!
	D_ASSERT(mFrameBufferID.IsValid());
	//D_ASSERT(DrawFrameBufferId != INVALID_BUFFER_ID);

	BindFrameBufferStatic(eBindFrameBufferTarget::READ_FRAMEBUFFER, mFrameBufferID);
	BindFrameBufferStatic(eBindFrameBufferTarget::DRAW_FRAMEBUFFER, DrawFrameBufferId);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<UINT32>(mask), static_cast<UINT32>(filter));
}


void FrameBuffer::BlitFrameBufferFrom(
	UINT32 ReadFrameBufferId, INT32 srcX0, INT32 srcY0, INT32 srcX1, INT32 srcY1,
	INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, GraphicsAPI::eBufferBitType mask,
	eImageInterpolation filter
) const noexcept
{
	//BackBuffer ID is zero!!
	//D_ASSERT(ReadFrameBufferId != INVALID_BUFFER_ID);
	D_ASSERT(mFrameBufferID.IsValid());

	BindFrameBufferStatic(eBindFrameBufferTarget::READ_FRAMEBUFFER, ReadFrameBufferId);
	BindFrameBufferStatic(eBindFrameBufferTarget::DRAW_FRAMEBUFFER, mFrameBufferID);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<UINT32>(mask), static_cast<UINT32>(filter));
}

void FrameBuffer::BlitFrameBufferToTexture(
	dooms::graphics::Texture* const drawTexture, INT32 srcX0, INT32 srcY0,
	INT32 srcX1, INT32 srcY1, INT32 dstX0, INT32 dstY0, INT32 dstX1, INT32 dstY1, 
	GraphicsAPI::eBufferBitType mask, eImageInterpolation filter
) const noexcept
{
	D_ASSERT(drawTexture != nullptr);
	
	BindFrameBufferStatic(eBindFrameBufferTarget::READ_FRAMEBUFFER, mFrameBufferID);
	BindFrameBufferStatic(eBindFrameBufferTarget::DRAW_FRAMEBUFFER, drawTexture->GetTextureBufferID());
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, static_cast<UINT32>(mask), static_cast<UINT32>(filter));
}

RenderBuffer& FrameBuffer::AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType, UINT32 width, UINT32 height)
{
	D_ASSERT(mFrameBufferID.IsValid());

	auto& createdRenderBuffer = mAttachedRenderBuffers.emplace_back(*this, renderBufferType, width, height);
	mClearBit |= static_cast<UINT32>(renderBufferType);

	CheckIsFrameBufferSuccesfullyCreated();
	return createdRenderBuffer;
}

RenderBuffer& dooms::graphics::FrameBuffer::AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType)
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
	case GraphicsAPI::eBufferBitType::COLOR:
	{
		SingleTexture colorTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			eTextureInternalFormat::RGBA16F, width, height, eTextureComponentFormat::RGBA, Texture::eDataType::FLOAT, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<UINT32>(mAttachedColorTextures.size()), static_cast<UINT32>(Texture::eBindTarget::TEXTURE_2D), colorTexture.GetTextureBufferID(), 0);

		mClearBit |= static_cast<UINT32>(GraphicsAPI::eBufferBitType::COLOR);
		mDrawTarget |= GL_COLOR_ATTACHMENT0 + mAttachedColorTextures.size();

		createdTexture = &mAttachedColorTextures.emplace_back(std::move(colorTexture));

		RefreshTargetDrawBufferContainer();
		SetTargetDrawBuffer();
		
		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH:
	{
		D_ASSERT(mAttachedDepthTextures.size() == 0);

		SingleTexture depthTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			eTextureInternalFormat::DEPTH_COMPONENT, width, height, eTextureComponentFormat::DEPTH_COMPONENT, Texture::eDataType::FLOAT, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, static_cast<UINT32>(Texture::eBindTarget::TEXTURE_2D), depthTexture.GetTextureBufferID(), 0);

		mAttachedDepthTextures.push_back(std::move(depthTexture));
		createdTexture = &mAttachedDepthTextures.back();

		mClearBit |= static_cast<UINT32>(GraphicsAPI::eBufferBitType::DEPTH);

		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
	{
		D_ASSERT(mAttachedDepthStencilTextures.size() == 0);

		SingleTexture depthStencilTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			eTextureInternalFormat::DEPTH24_STENCIL8, width, height, eTextureComponentFormat::DEPTH_STENCIL, Texture::eDataType::UNSIGNED_INT_24_8, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, static_cast<UINT32>(Texture::eBindTarget::TEXTURE_2D), depthStencilTexture.GetTextureBufferID(), 0);

		mAttachedDepthStencilTextures.push_back(std::move(depthStencilTexture));
		createdTexture = &mAttachedDepthStencilTextures.back();

		mClearBit |= static_cast<UINT32>(GraphicsAPI::eBufferBitType::DEPTH_STENCIL);
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



		
		
