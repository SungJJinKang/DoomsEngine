#include "FrameBuffer.h"

#include "../Graphics_Setting.h"



using namespace doom::graphics;


doom::graphics::FrameBuffer::FrameBuffer()
{
}

FrameBuffer::FrameBuffer(unsigned int defaultWidth, unsigned int defaultHeight)
	: mDefaultWidth{ defaultWidth }, mDefaultHeight{ defaultHeight }, mClearBit{ 0 }
{
	mAttachedRenderBuffers.reserve(RESERVED_RENDERBUFFER_COUNT);
	mAttachedColorTextures.reserve(RESERVED_COLOR_TEXTURE_COUNT);
	mAttachedDepthTextures.reserve(RESERVED_DEPTH_TEXTURE_COUNT);
	mAttachedDepthStencilTextures.reserve(RESERVED_DEPTH_STENCIL_TEXTURE_COUNT);
}

void doom::graphics::FrameBuffer::GenerateBuffer(unsigned int defaultWidth, unsigned int defaultHeight)
{
	mDefaultWidth = defaultWidth;
	mDefaultHeight = defaultHeight;
	glGenFramebuffers(1, &(mFrameBufferID));
}


void FrameBuffer::RefreshTargetDrawBufferContainer()
{
	mTargetDrawBufferContainer.clear();
	mTargetDrawBufferContainer.reserve(mAttachedColorTextures.size());

	for (unsigned int i = 0; i < mAttachedColorTextures.size(); i++)
	{
		mTargetDrawBufferContainer.emplace_back(GL_COLOR_ATTACHMENT0 + i);
	}
}

void FrameBuffer::SetTargetDrawBuffer()
{
	glDrawBuffers(static_cast<int>(mTargetDrawBufferContainer.size()), mTargetDrawBufferContainer.data());
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

const doom::graphics::SingleTexture& FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, unsigned int index) const
{
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR:
		return mAttachedColorTextures[index];
		break;

	case GraphicsAPI::eBufferBitType::DEPTH:
		return mAttachedDepthTextures[index];
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
		return mAttachedDepthStencilTextures[index];
		break;
	default:
		NEVER_HAPPEN;
	}
}

doom::graphics::SingleTexture& FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType bufferType, unsigned int index)
{
	switch (bufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR:
		D_ASSERT(index >= 0 && index < mAttachedColorTextures.size());
		return mAttachedColorTextures[index];
		break;

	case GraphicsAPI::eBufferBitType::DEPTH:
		D_ASSERT(index >= 0 && index < mAttachedDepthTextures.size());
		return mAttachedDepthTextures[index];
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
		D_ASSERT(index >= 0 && index < mAttachedDepthStencilTextures.size());
		return mAttachedDepthStencilTextures[index];
		break;
	default:
		NEVER_HAPPEN;
	}
}

bool doom::graphics::FrameBuffer::IsGenerated()
{
	return mFrameBufferID != 0;
}

RenderBuffer& FrameBuffer::AttachRenderBuffer(GraphicsAPI::eBufferBitType renderBufferType, unsigned int width, unsigned int height)
{
	D_ASSERT(mFrameBufferID != 0);
	auto& createdRenderBuffer = mAttachedRenderBuffers.emplace_back(*this, renderBufferType, width, height);
	mClearBit |= static_cast<unsigned int>(renderBufferType);

	CheckIsFrameBufferSuccesfullyCreated();
	return createdRenderBuffer;
}

SingleTexture& FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType frameBufferType, unsigned int width, unsigned int height)
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
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<unsigned int>(mAttachedColorTextures.size()), static_cast<unsigned int>(Texture::eBindTarget::TEXTURE_2D), colorTexture.GetID(), 0);

		mClearBit |= static_cast<unsigned int>(GraphicsAPI::eBufferBitType::COLOR);
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
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, static_cast<unsigned int>(Texture::eBindTarget::TEXTURE_2D), depthTexture.GetID(), 0);

		mAttachedDepthTextures.push_back(std::move(depthTexture));
		createdTexture = &mAttachedDepthTextures.back();

		mClearBit |= static_cast<unsigned int>(GraphicsAPI::eBufferBitType::DEPTH);

		break;
	}
	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
	{
		D_ASSERT(mAttachedDepthStencilTextures.size() == 0);

		SingleTexture depthStencilTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			eTextureInternalFormat::DEPTH24_STENCIL8, width, height, eTextureComponentFormat::DEPTH_STENCIL, Texture::eDataType::UNSIGNED_INT_24_8, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, static_cast<unsigned int>(Texture::eBindTarget::TEXTURE_2D), depthStencilTexture.GetID(), 0);

		mAttachedDepthStencilTextures.push_back(std::move(depthStencilTexture));
		createdTexture = &mAttachedDepthStencilTextures.back();

		mClearBit |= static_cast<unsigned int>(GraphicsAPI::eBufferBitType::DEPTH_STENCIL);
		break;

	}
		
	default:
		NEVER_HAPPEN;
		break;

	}
	
	return *createdTexture;
}



		
		
