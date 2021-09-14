#include "DefferedRenderingFrameBuffer.h"

#include "../Graphics_Server.h"

doom::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
{
	FrameBuffer::GenerateBuffer(Graphics_Server::GetScreenWidth(), Graphics_Server::GetScreenHeight());

	//with renderbuffer, can't do post-processing
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::GetScreenWidth(), Graphics_Server::GetScreenHeight());
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::GetScreenWidth(), Graphics_Server::GetScreenHeight());
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::GetScreenWidth(), Graphics_Server::GetScreenHeight());
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferType::DEPTH, Graphics_Server::GetScreenWidth(), Graphics_Server::GetScreenHeight());

}

void doom::graphics::DefferedRenderingFrameBuffer::BindGBufferTextures()
{
	for (unsigned int i = 0; i < 3; i++)
	{
		FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, i).BindTextureWithUnit(i);
	}
}
