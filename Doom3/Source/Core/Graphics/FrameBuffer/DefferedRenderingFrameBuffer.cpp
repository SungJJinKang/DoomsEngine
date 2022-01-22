#include "DefferedRenderingFrameBuffer.h"

#include "../Graphics_Server.h"
#include "../GraphicsAPI/graphicsAPISetting.h"
#include <Rendering/Camera.h>

dooms::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
{
	//with renderbuffer, can't do post-processing

	//Position
	FrameBuffer::AttachColorTextureToFrameBuffer(0, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
	//Normal
	FrameBuffer::AttachColorTextureToFrameBuffer(1, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
	//Albedo
	FrameBuffer::AttachColorTextureToFrameBuffer(2, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
	//Depth
	FrameBuffer::AttachDepthTextureToFrameBuffer(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight());
	
}

void dooms::graphics::DefferedRenderingFrameBuffer::BlitDepthBufferToScreenBuffer()
{
	FrameBuffer::BlitFrameBufferFromToFrameBuffer(this, nullptr, 0, 0, GetDefaultWidth(), GetDefaultHeight(), 0, 0, graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight(), GraphicsAPI::eBufferBitType::DEPTH_BUFFER, GraphicsAPI::eImageInterpolation::IMAGE_INTERPOLATION_NEAREST);

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
	static const math::Vector4 ZERO_ZERO_ZERO_ONE{ 0.0f, 0.0f, 0.0f, 1.0f };
	static math::Vector4 TARGET_COLORS[3] =
	{
		ZERO_ZERO_ZERO_ONE,
		ZERO_ZERO_ZERO_ONE,
		camera->mClearColor
	};

	BindFrameBuffer();
	ClearColorTexture(0, TARGET_COLORS[0][0], TARGET_COLORS[0][1], TARGET_COLORS[0][2], TARGET_COLORS[0][3]);
	ClearColorTexture(1, TARGET_COLORS[1][0], TARGET_COLORS[1][1], TARGET_COLORS[1][2], TARGET_COLORS[1][3]);
	ClearColorTexture(2, TARGET_COLORS[2][0], TARGET_COLORS[2][1], TARGET_COLORS[2][2], TARGET_COLORS[2][3]);
	//GraphicsAPI::ClearBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER);
	//GraphicsAPI::ClearBuffer(GraphicsAPI::eBufferBitType::DEPTH_BUFFER);
	ClrearDepthTexture(GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);
	
}
