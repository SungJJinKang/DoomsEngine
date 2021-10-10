#include "RenderBuffer.h"

#include "FrameBuffer.h"
#include "../GraphicsAPI.h"
#include "../Graphics_Setting.h"

using namespace doom::graphics;

RenderBuffer::RenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferBitType frameBufferType, unsigned int width, unsigned int height)
{
	ownerFrameBuffer.BindFrameBuffer();

	glGenRenderbuffers(1, &(mRenderBufferID));
	BindRenderBuffer();



	switch (frameBufferType)
	{
	case GraphicsAPI::eBufferBitType::COLOR:
		if (Graphics_Setting::GetMultiSamplingNum() > 0)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(eTextureInternalFormat::RGBA16F), width, height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Setting::GetMultiSamplingNum(), static_cast<unsigned int>(eTextureInternalFormat::RGBA16F), width, height);
		}
				
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mRenderBufferID);
		break;

	case GraphicsAPI::eBufferBitType::DEPTH:
		if (Graphics_Setting::GetMultiSamplingNum() > 0)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(eTextureInternalFormat::DEPTH_COMPONENT), width, height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Setting::GetMultiSamplingNum(), static_cast<unsigned int>(eTextureInternalFormat::DEPTH_COMPONENT), width, height);
		}

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferID);
		break;

	case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
		if (Graphics_Setting::GetMultiSamplingNum() > 0)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(eTextureInternalFormat::DEPTH24_STENCIL8), width, height);
		}
		else
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Setting::GetMultiSamplingNum(), static_cast<unsigned int>(eTextureInternalFormat::DEPTH24_STENCIL8), width, height);
		}

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferID);
		break;

	default:
		NEVER_HAPPEN;
		break;

	}
}

doom::graphics::RenderBuffer::~RenderBuffer()
{
	if (mRenderBufferID.Get() != 0)
	{
		glDeleteRenderbuffers(1, &(mRenderBufferID));
	}
}

