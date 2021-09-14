#include "DefferedRenderingFrameBuffer.h"

#include "../Graphics_Server.h"
#include "../Graphics_Setting.h"

doom::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
{
	FrameBuffer::GenerateBuffer(Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());

	//with renderbuffer, can't do post-processing
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::DEPTH, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());

	CheckIsFrameBufferSuccesfullyCreated();
}

void doom::graphics::DefferedRenderingFrameBuffer::BindGBufferTextures()
{
	for (unsigned int i = 0; i < 3; i++)
	{
		FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, i).BindTextureWithUnit(i);
	}
}
