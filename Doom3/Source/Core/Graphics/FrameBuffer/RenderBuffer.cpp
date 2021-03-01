#include "RenderBuffer.h"

#include "FrameBuffer.h"
#include "../GraphicsAPI.h"
#include "../Graphics_Server.h"

using namespace doom::graphics;

RenderBuffer::RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferType frameBufferType, unsigned int width, unsigned int height)
{
	ownerFrameBuffer.BindFrameBuffer();

	glGenRenderbuffers(1, &(this->mRenderBufferID.GetReference()));
	this->BindRenderBuffer();



	switch (frameBufferType)
	{
	case GraphicsAPI::eBufferType::COLOR:
		if (Graphics_Server::MultiSamplingNum > 0)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(eTextureInternalFormat::RGBA16F), width, height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Server::MultiSamplingNum, static_cast<unsigned int>(eTextureInternalFormat::RGBA16F), width, height);
		}
				
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->mRenderBufferID);
		break;

	case GraphicsAPI::eBufferType::DEPTH:
		if (Graphics_Server::MultiSamplingNum > 0)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(eTextureInternalFormat::DEPTH_COMPONENT), width, height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Server::MultiSamplingNum, static_cast<unsigned int>(eTextureInternalFormat::DEPTH_COMPONENT), width, height);
		}

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->mRenderBufferID);
		break;

	case GraphicsAPI::eBufferType::DEPTH_STENCIL:
		if (Graphics_Server::MultiSamplingNum > 0)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(eTextureInternalFormat::DEPTH24_STENCIL8), width, height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Server::MultiSamplingNum, static_cast<unsigned int>(eTextureInternalFormat::DEPTH24_STENCIL8), width, height);
		}

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->mRenderBufferID);
		break;

	default:
		NODEFAULT;
		break;

	}
}

doom::graphics::RenderBuffer::~RenderBuffer()
{
	if (this->mRenderBufferID.GetReference() != 0)
	{
		glDeleteRenderbuffers(1, &(this->mRenderBufferID.GetReference()));
	}
}

