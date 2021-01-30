#include "FrameBuffer.h"



using namespace doom::graphics;


FrameBuffer::FrameBuffer(unsigned int width, unsigned int height) 
	: mWidth{ width }, mHeight{ height }
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
		D_DEBUG_LOG({ "fail frame buffer", std::to_string(glCheckFramebufferStatus(GL_FRAMEBUFFER)) }, logger::LogType::D_ERROR);
	}
}

void FrameBuffer::AttachRenderBuffer(Graphics::eBufferType renderBufferType)
{
	this->mAttachedRenderBuffers.emplace_back(*this, renderBufferType, this->mWidth, this->mHeight);
	FrameBuffer::CheckIsFrameBufferSuccesfullyCreated();
}

void FrameBuffer::AttachTextureBuffer(Graphics::eBufferType frameBufferType)
{
	this->BindFrameBuffer();

	/*
	switch (frameBufferType)
	{
	case FrameBufferType::COLOR:
		SingleTexture texture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, Texture::eInternalFormat:: };

		singleTexture->ResetTexture(textureTarget, ColorTextureFormat, width, height, GL_RGB, GL_UNSIGNED_BYTE); // FOR HDR , USE RGB16F
	
		
		this->mAttachedColorTextures.push_back(std::move())

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + this->getColorTexutureCount() - 1, textureTarget, texture->id, 0);
		this->clearBufferBitfield |= GL_COLOR_BUFFER_BIT;
		break;

	case FrameBufferType::DEPTH:
		SingleTexture texture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, Texture::eInternalFormat:: };

		singleTexture->ResetTexture(textureTarget, GL_DEPTH_COMPONENT, width, height, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, std::bind(&(FrameBuffer::ConfigureDepthTexture), singleTexture));
	
		this->mAttachedDepthextures.push_back(std::move())

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureTarget, texture->id, 0);
		this->clearBufferBitfield |= GL_DEPTH_BUFFER_BIT;
		break;

	case FrameBufferType::DEPTH_STENCIL:
		SingleTexture texture{ Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, Texture::eInternalFormat:: };

		singleTexture->ResetTexture(textureTarget, GL_DEPTH24_STENCIL8, width, height, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);


		this->mAttachedDepthStencilTextures.push_back(std::move())

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, textureTarget, texture->id, 0);
		this->clearBufferBitfield |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
		break;
	default:
		NODEFAULT;
		break;

	}
	*/
}



		
		
