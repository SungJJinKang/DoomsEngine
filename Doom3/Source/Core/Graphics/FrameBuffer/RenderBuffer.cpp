#include "RenderBuffer.h"

#include "FrameBuffer.h"
#include "../GraphicsAPI/graphicsAPISetting.h"

using namespace dooms::graphics;

RenderBuffer::RenderBuffer()
	: mRenderBufferID()
{
}

RenderBuffer::RenderBuffer
(
	FrameBuffer& ownerFrameBuffer, 
	GraphicsAPI::eBufferAttachmentType frameBufferType,
	UINT32 width, 
	UINT32 height
)
	: mRenderBufferID()
{
	CreateRenderBuffer(ownerFrameBuffer, frameBufferType, width, height);
}

bool RenderBuffer::CreateRenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eBufferAttachmentType frameBufferType, UINT32 width, UINT32 height)
{
	bool isSuccess = false;

	D_ASSERT(mRenderBufferID.IsValid() == false);
	if(mRenderBufferID.IsValid() == false)
	{
		mFrameBufferType = frameBufferType;
		mWidth = width;
		mHeight = height;

		ownerFrameBuffer.BindFrameBuffer();

		mRenderBufferID = GraphicsAPI::CreateRenderBufferObject(1)[0];
		BindRenderBuffer();


		switch (frameBufferType)
		{
		case GraphicsAPI::eBufferAttachmentType::ATTACHMENT_COLOR0:
		case GraphicsAPI::eBufferAttachmentType::ATTACHMENT_COLOR1:
		case GraphicsAPI::eBufferAttachmentType::ATTACHMENT_COLOR2:
		case GraphicsAPI::eBufferAttachmentType::ATTACHMENT_COLOR3:

			GraphicsAPI::AllocateRenderBufferMemory(mRenderBufferID, GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA16F, width, height, graphicsAPISetting::GetMultiSamplingNum());
			GraphicsAPI::AttachRenderBufferToFrameBuffer(mRenderBufferID.GetBufferID(), ownerFrameBuffer.GetFrameBufferID(), frameBufferType);
			
			break;

		case GraphicsAPI::eBufferAttachmentType::ATTACHMENT_DEPTH:

			GraphicsAPI::AllocateRenderBufferMemory(mRenderBufferID, GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT, width, height, graphicsAPISetting::GetMultiSamplingNum());
			GraphicsAPI::AttachRenderBufferToFrameBuffer(mRenderBufferID.GetBufferID(), ownerFrameBuffer.GetFrameBufferID(), GraphicsAPI::eBufferAttachmentType::ATTACHMENT_DEPTH);

			break;

		case GraphicsAPI::eBufferAttachmentType::ATTACHMENT_DEPTH_STENCIL:
			
			GraphicsAPI::AllocateRenderBufferMemory(mRenderBufferID, GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8, width, height, graphicsAPISetting::GetMultiSamplingNum());
			GraphicsAPI::AttachRenderBufferToFrameBuffer(mRenderBufferID.GetBufferID(), ownerFrameBuffer.GetFrameBufferID(), GraphicsAPI::eBufferAttachmentType::ATTACHMENT_DEPTH_STENCIL);

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
		GraphicsAPI::DestroyRenderBuffer(mRenderBufferID);
	}
}

