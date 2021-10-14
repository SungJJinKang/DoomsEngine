#include "FrameBuffer.h"


using namespace doom::graphics;


doom::graphics::FrameBuffer::FrameBuffer()
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

void doom::graphics::FrameBuffer::GenerateBuffer(UINT32 defaultWidth, UINT32 defaultHeight)
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


FrameBuffer::~FrameBuffer()
{
	if (mFrameBufferID != 0)
	{
		glDeleteFramebuffers(1, &(mFrameBufferID));
	}
	
}




void FrameBuffer::CheckIsFrameBufferSuccesfullyCreated() noexcept
{
	BindFrameBuffer();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{//Fail Creating FrameBuffer
		D_ASSERT(false);
		D_DEBUG_LOG({ "fail frame buffer", std::to_string(glCheckFramebufferStatus(GL_FRAMEBUFFER)) }, logger::eLogType::D_ERROR);
	}
}

const doom::graphics::SingleTexture* FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index) const
{
	const doom::graphics::SingleTexture* targetTexture = nullptr;
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

doom::graphics::SingleTexture* FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, UINT32 index)
{
	doom::graphics::SingleTexture* targetTexture = nullptr;
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

bool doom::graphics::FrameBuffer::IsGenerated()
{
	return mFrameBufferID != 0;
}

RenderBuffer& FrameBuffer::AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType, UINT32 width, UINT32 height)
{
	D_ASSERT(mFrameBufferID != 0);
	auto& createdRenderBuffer = mAttachedRenderBuffers.emplace_back(*this, renderBufferType, width, height);
	mClearBit |= static_cast<UINT32>(renderBufferType);

	CheckIsFrameBufferSuccesfullyCreated();
	return createdRenderBuffer;
}

RenderBuffer& doom::graphics::FrameBuffer::AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType)
{
	return AttachRenderBuffer(renderBufferType, mDefaultWidth, mDefaultHeight);
}

SingleTexture& FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height)
{
	D_ASSERT(mFrameBufferID != 0);

	BindFrameBuffer();

	doom::graphics::SingleTexture* createdTexture = nullptr;
	
	switch (frameBufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR:
	{
		SingleTexture colorTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			eTextureInternalFormat::RGBA16F, width, height, eTextureComponentFormat::RGBA, Texture::eDataType::FLOAT, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<UINT32>(mAttachedColorTextures.size()), static_cast<UINT32>(Texture::eBindTarget::TEXTURE_2D), colorTexture.GetID(), 0);

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
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, static_cast<UINT32>(Texture::eBindTarget::TEXTURE_2D), depthTexture.GetID(), 0);

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
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, static_cast<UINT32>(Texture::eBindTarget::TEXTURE_2D), depthStencilTexture.GetID(), 0);

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

SingleTexture& doom::graphics::FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType)
{
	return AttachTextureBuffer(frameBufferType, mDefaultWidth, mDefaultHeight);
}



		
		
