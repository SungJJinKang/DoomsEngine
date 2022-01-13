#include "DefferedRenderingFrameBuffer.h"

#include "../Graphics_Server.h"
#include "../GraphicsAPI/graphicsAPISetting.h"
#include <Rendering/Camera.h>

dooms::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
{
	FrameBuffer::GenerateBuffer(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());

	//with renderbuffer, can't do post-processing

	//Position
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
	//Normal
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
	//Albedo
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
	//Depth
	FrameBuffer::AttachTextureBuffer(GraphicsAPI::eBufferBitType::DEPTH_BUFFER, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());

	CheckIsFrameBufferSuccesfullyCreated();
}

void dooms::graphics::DefferedRenderingFrameBuffer::BlitDepthBufferToScreenBuffer() const
{
	FrameBuffer::BlitFrameBufferTo(0, 0, 0, GetDefaultWidth(), GetDefaultHeight(), 0, 0, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight(), GraphicsAPI::eBufferBitType::DEPTH_BUFFER, GraphicsAPI::eImageInterpolation::IMAGE_INTERPOLATION_NEAREST);

}

void dooms::graphics::DefferedRenderingFrameBuffer::BindGBufferTextures()
{
	for (UINT32 i = 0; i < 3; i++)
	{
		FrameBuffer::GetFrameBufferTexture(GraphicsAPI::eBufferBitType::COLOR_BUFFER, i)->BindTextureWithUnit(i);
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

	static const std::vector<GraphicsAPI::eBufferMode> BUFFER_MODES =
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
		camera->mClearColor
	};

	GraphicsAPI::SetDrawBuffers(3, BUFFER_MODES.data());
	GraphicsAPI::ClearSpecificBuffer(GraphicsAPI::eBufferType::COLOR, 0, TARGET_COLORS[0][0], TARGET_COLORS[0][1], TARGET_COLORS[0][2], TARGET_COLORS[0][3]);
	GraphicsAPI::ClearSpecificBuffer(GraphicsAPI::eBufferType::COLOR, 1, TARGET_COLORS[1][0], TARGET_COLORS[1][1], TARGET_COLORS[1][2], TARGET_COLORS[1][3]);
	GraphicsAPI::ClearSpecificBuffer(GraphicsAPI::eBufferType::COLOR, 2, TARGET_COLORS[2][0], TARGET_COLORS[2][1], TARGET_COLORS[2][2], TARGET_COLORS[2][3]);
	//GraphicsAPI::ClearBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER);
	//GraphicsAPI::ClearBuffer(GraphicsAPI::eBufferBitType::DEPTH_BUFFER);
	GraphicsAPI::ClearBufferDepthBuffer(GetFrameBufferID(), GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);

	SetTargetDrawBuffer();
}
