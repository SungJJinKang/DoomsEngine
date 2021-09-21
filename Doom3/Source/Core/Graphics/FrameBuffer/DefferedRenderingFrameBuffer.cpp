#include "DefferedRenderingFrameBuffer.h"

#include "../Graphics_Server.h"
#include "../Graphics_Setting.h"

doom::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
{
	FrameBuffer::GenerateBuffer(Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());

	//with renderbuffer, can't do post-processing

	//Position
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	
	//Normal
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	
	//Albedo
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());
	
	//Depth
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::DEPTH, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());

	CheckIsFrameBufferSuccesfullyCreated();
}

void doom::graphics::DefferedRenderingFrameBuffer::BlitDepthBufferToScreenBuffer() const
{
	FrameBuffer::BlitBufferTo(0, 0, 0, GetDefaultWidth(), GetDefaultHeight(), 0, 0, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight(), GraphicsAPI::eBufferBitType::DEPTH, FrameBuffer::eImageInterpolation::NEAREST);

}

void doom::graphics::DefferedRenderingFrameBuffer::BindGBufferTextures()
{
	for (unsigned int i = 0; i < 3; i++)
	{
		FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType::COLOR, i).BindTextureWithUnit(i);
	}
}
