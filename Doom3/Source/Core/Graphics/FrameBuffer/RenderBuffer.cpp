#include "RenderBuffer.h"

#include "FrameBuffer.h"
#include "../GraphicsAPI/graphicsAPISetting.h"

using namespace dooms::graphics;

void RenderBuffer::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DeleteRenderBuffers();
}

RenderBuffer::RenderBuffer()
	: mRenderBufferID()
{
}

RenderBuffer::RenderBuffer
(
	FrameBuffer& ownerFrameBuffer, 
	GraphicsAPI::eFrameBufferAttachmentPoint frameBufferType,
	UINT32 width, 
	UINT32 height
)
	: mRenderBufferID()
{
	CreateRenderBuffer(ownerFrameBuffer, frameBufferType, width, height);
}

bool RenderBuffer::CreateRenderBuffer(FrameBuffer& ownerFrameBuffer, GraphicsAPI::eFrameBufferAttachmentPoint frameBufferType, UINT32 width, UINT32 height)
{
	bool isSuccess = false;

	D_ASSERT(mRenderBufferID.IsValid() == false);
	if(mRenderBufferID.IsValid() == false)
	{
		mFrameBufferType = frameBufferType;
		mWidth = width;
		mHeight = height;

		ownerFrameBuffer.BindFrameBuffer();
		
		mRenderBufferID = GraphicsAPI::CreateRenderBufferObject();
		BindRenderBuffer();


		switch (frameBufferType)
		{
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT1:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT2:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT3:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT4:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT5:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT6:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT7:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT8:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT9:
		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT10:

			GraphicsAPI::AllocateRenderBufferMemory(mRenderBufferID, GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA16F, width, height, graphicsAPISetting::GetMultiSamplingNum());
			GraphicsAPI::AttachRenderBufferToFrameBuffer(mRenderBufferID.GetBufferID(), ownerFrameBuffer.GetFrameBufferID(), frameBufferType);
			
			break;

		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT:

			GraphicsAPI::AllocateRenderBufferMemory(mRenderBufferID, GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32, width, height, graphicsAPISetting::GetMultiSamplingNum());
			GraphicsAPI::AttachRenderBufferToFrameBuffer(mRenderBufferID.GetBufferID(), ownerFrameBuffer.GetFrameBufferID(), GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT);

			break;

		case GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT:
			
			GraphicsAPI::AllocateRenderBufferMemory(mRenderBufferID, GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8, width, height, graphicsAPISetting::GetMultiSamplingNum());
			GraphicsAPI::AttachRenderBufferToFrameBuffer(mRenderBufferID.GetBufferID(), ownerFrameBuffer.GetFrameBufferID(), GraphicsAPI::eFrameBufferAttachmentPoint::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT);

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
	if (mRenderBufferID.IsValid())
	{
		GraphicsAPI::DestroyRenderBuffer(mRenderBufferID);
		mRenderBufferID.Reset();
	}
}

