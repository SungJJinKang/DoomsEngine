#include "DefferedRenderingFrameBuffer.h"

#include "../Graphics_Server.h"
#include "../Graphics_Setting.h"
#include <Rendering/Camera.h>

dooms::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
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

void dooms::graphics::DefferedRenderingFrameBuffer::BlitDepthBufferToScreenBuffer() const
{
	FrameBuffer::BlitFrameBufferTo(0, 0, 0, GetDefaultWidth(), GetDefaultHeight(), 0, 0, Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight(), GraphicsAPI::eBufferBitType::DEPTH, FrameBuffer::eImageInterpolation::NEAREST);

}

void dooms::graphics::DefferedRenderingFrameBuffer::BindGBufferTextures()
{
	for (UINT32 i = 0; i < 3; i++)
	{
		FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType::COLOR, i)->BindTextureWithUnit(i);
	}
}

void dooms::graphics::DefferedRenderingFrameBuffer::ClearFrameBuffer(const Camera* const camera)
{
	graphics::FrameBuffer::BindFrameBuffer();
			
	static const GraphicsAPI::eBufferType BUFFER_TYPES[3] =
	{
		GraphicsAPI::eBufferType::COLOR,
		GraphicsAPI::eBufferType::COLOR,
		GraphicsAPI::eBufferType::COLOR
	};

	static const GraphicsAPI::eBufferMode BUFFER_MODES[3] =
	{ 
		GraphicsAPI::eBufferMode::COLOR_ATTACHMENT0, 
		GraphicsAPI::eBufferMode::COLOR_ATTACHMENT1,
		GraphicsAPI::eBufferMode::COLOR_ATTACHMENT2
	};

	static const math::Vector4 ZERO_ZERO_ZERO_ONE{ 0.0f, 0.0f, 0.0f, 1.0f };
			

	static math::Vector4 TARGET_COLORS[3] =
	{
		ZERO_ZERO_ZERO_ONE,
		ZERO_ZERO_ZERO_ONE,
		math::Vector4(0, 0, 0, 0)
	};

	TARGET_COLORS[2] = camera->mClearColor;

	GraphicsAPI::ClearSpecificBuffer(3, BUFFER_TYPES, BUFFER_MODES, TARGET_COLORS);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	SetTargetDrawBuffer();
}
