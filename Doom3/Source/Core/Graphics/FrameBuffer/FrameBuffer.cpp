#include "FrameBuffer.h"



using namespace doom::graphics;


FrameBuffer::FrameBuffer(unsigned int defaultWidth, unsigned int defaultHeight)
	: mDefaultWidth{ defaultWidth }, mDefaultHeight{ defaultHeight }, mClearBit{ 0 }
{
	mAttachedRenderBuffers.reserve(RESERVED_RENDERBUFFER_COUNT);
	mAttachedColorTextures.reserve(RESERVED_COLOR_TEXTURE_COUNT);
	mAttachedDepthextures.reserve(RESERVED_DEPTH_TEXTURE_COUNT);
	mAttachedDepthStencilTextures.reserve(RESERVED_DEPTH_STENCIL_TEXTURE_COUNT);

	glGenFramebuffers(1, &(this->mFbo));

}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &(this->mFbo));
}




void FrameBuffer::CheckIsFrameBufferSuccesfullyCreated() noexcept
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{//Fail Creating FrameBuffer
		D_DEBUG_LOG({ "fail frame buffer", std::to_string(glCheckFramebufferStatus(GL_FRAMEBUFFER)) }, logger::eLogType::D_ERROR);
	}
}

void FrameBuffer::AttachRenderBuffer(GraphicsAPI::eBufferType renderBufferType, unsigned int width, unsigned int height)
{
	this->mAttachedRenderBuffers.emplace_back(*this, renderBufferType, width, height);
	FrameBuffer::CheckIsFrameBufferSuccesfullyCreated();
}

void FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height)
{
	this->BindFrameBuffer();

	
	switch (frameBufferType)
	{
	case GraphicsAPI::eBufferType::COLOR:
	{
		SingleTexture colorTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			Texture::eInternalFormat::RGB, width, height, Texture::eDataFormat::RGB, Texture::eDataType::UNSIGNED_BYTE, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<unsigned int>(this->mAttachedColorTextures.size() - 1), static_cast<unsigned int>(GraphicsAPI::eBufferType::COLOR), colorTexture.GetID(), 0);

		this->mAttachedColorTextures.push_back(std::move(colorTexture));

		this->mClearBit |= static_cast<unsigned int>(GraphicsAPI::eBufferType::COLOR);
		break;
	}
	case GraphicsAPI::eBufferType::DEPTH:
	{
		D_ASSERT(this->mAttachedDepthextures.size() == 0);

		SingleTexture depthTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			Texture::eInternalFormat::DEPTH_COMPONENT, width, height, Texture::eDataFormat::DEPTH_COMPONENT, Texture::eDataType::UNSIGNED_BYTE, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT + static_cast<unsigned int>(this->mAttachedDepthextures.size() - 1), static_cast<unsigned int>(GraphicsAPI::eBufferType::DEPTH), depthTexture.GetID(), 0);

		this->mAttachedDepthextures.push_back(std::move(depthTexture));

		this->mClearBit |= static_cast<unsigned int>(GraphicsAPI::eBufferType::DEPTH);
		break;
	}
	case GraphicsAPI::eBufferType::DEPTH_STENCIL:
	{
		D_ASSERT(this->mAttachedDepthStencilTextures.size() == 0);

		SingleTexture depthStencilTexture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D,
			Texture::eInternalFormat::DEPTH_STENCIL, width, height, Texture::eDataFormat::DEPTH_STENCIL, Texture::eDataType::UNSIGNED_BYTE, NULL };
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT + static_cast<unsigned int>(this->mAttachedDepthStencilTextures.size() - 1), static_cast<unsigned int>(GraphicsAPI::eBufferType::DEPTH_STENCIL), depthStencilTexture.GetID(), 0);

		this->mAttachedDepthStencilTextures.push_back(std::move(depthStencilTexture));

		this->mClearBit |= static_cast<unsigned int>(GraphicsAPI::eBufferType::DEPTH_STENCIL);
		break;

	}
		
	default:
		NODEFAULT;
		break;

	}
	
}



		
		
