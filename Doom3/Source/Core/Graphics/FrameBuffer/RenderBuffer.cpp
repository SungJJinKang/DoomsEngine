#include "RenderBuffer.h"

#include "FrameBuffer.h"
#include "../GraphicsAPI.h"
#include "../Graphics_Setting.h"

using namespace dooms::graphics;

RenderBuffer::RenderBuffer()
	: mRenderBufferID()
{
}

RenderBuffer::RenderBuffer
(
	FrameBuffer& ownerFrameBuffer, 
	GraphicsAPI::eBufferBitType frameBufferType, 
	UINT32 width, 
	UINT32 height
)
	: mRenderBufferID()
{
	CreateRenderBuffer(ownerFrameBuffer, frameBufferType, width, height);
}

bool RenderBuffer::CreateRenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferBitType frameBufferType, UINT32 width, UINT32 height)
{
	bool isSuccess = false;

	D_ASSERT(mRenderBufferID.IsValid() == false);
	if(mRenderBufferID.IsValid() == false)
	{
		mFrameBufferType = frameBufferType;
		mWidth = width;
		mHeight = height;

		ownerFrameBuffer.BindFrameBuffer();

		glGenRenderbuffers(1, &(mRenderBufferID));
		BindRenderBuffer();


		switch (frameBufferType)
		{
		case GraphicsAPI::eBufferBitType::COLOR:
			if (Graphics_Setting::GetMultiSamplingNum() > 0)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, static_cast<UINT32>(eTextureInternalFormat::RGBA16F), width, height);
			}
			else
			{
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Setting::GetMultiSamplingNum(), static_cast<UINT32>(eTextureInternalFormat::RGBA16F), width, height);
			}

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mRenderBufferID);
			break;

		case GraphicsAPI::eBufferBitType::DEPTH:
			if (Graphics_Setting::GetMultiSamplingNum() > 0)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, static_cast<UINT32>(eTextureInternalFormat::DEPTH_COMPONENT), width, height);
			}
			else
			{
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Setting::GetMultiSamplingNum(), static_cast<UINT32>(eTextureInternalFormat::DEPTH_COMPONENT), width, height);
			}

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferID);
			break;

		case GraphicsAPI::eBufferBitType::DEPTH_STENCIL:
			if (Graphics_Setting::GetMultiSamplingNum() > 0)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, static_cast<UINT32>(eTextureInternalFormat::DEPTH24_STENCIL8), width, height);
			}
			else
			{
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, Graphics_Setting::GetMultiSamplingNum(), static_cast<UINT32>(eTextureInternalFormat::DEPTH24_STENCIL8), width, height);
			}

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBufferID);
			break;

		default:
			NEVER_HAPPEN;
			break;

		}

		isSuccess = true;
	}

	
	return isSuccess;
}

dooms::graphics::RenderBuffer::~RenderBuffer()
{
	DeleteRenderBuffers();
}

void RenderBuffer::DeleteRenderBuffers()
{
	if (mRenderBufferID)
	{
		glDeleteRenderbuffers(1, &(mRenderBufferID));
	}
}

