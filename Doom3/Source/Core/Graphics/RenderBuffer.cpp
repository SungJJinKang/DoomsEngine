#include "RenderBuffer.h"

#include "FrameBuffer.h"
#include "Graphics.h"
using namespace doom::graphics;

RenderBuffer::RenderBuffer(FrameBuffer& ownerFrameBuffer, FrameBuffer::eFrameBufferType frameBufferType, unsigned int width, unsigned int height)
{
	ownerFrameBuffer.BindFrameBuffer();

	glGenRenderbuffers(1, &(this->mID));
	this->BindRenderBuffer();


	switch (frameBufferType)
	{
	case FrameBuffer::eFrameBufferType::COLOR:
		if (Graphics::Is_MULTI_SAMPLE == false)
			glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, width, height);
		else
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->mID);
		break;

	case FrameBuffer::eFrameBufferType::DEPTH:
		if (Graphics::Is_MULTI_SAMPLE == false)
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		else
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT24, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->mID);
		break;

	case FrameBuffer::eFrameBufferType::DEPTH_STENCIL:
		if (Graphics::Is_MULTI_SAMPLE == false)
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		else
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->mID);
		break;

	default:
		NODEFAULT;
		break;

	}
}

