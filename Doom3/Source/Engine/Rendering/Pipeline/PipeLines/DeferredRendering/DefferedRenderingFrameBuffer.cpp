#include "DefferedRenderingFrameBuffer.h"

#include <Graphics/Graphics_Server.h>
#include <Graphics/GraphicsAPI/graphicsAPISetting.h>
#include <Rendering/Camera.h>

#include "Graphics/Texture/TextureView.h"

#define DEFAULT_GBUFFER_RESOLUTION_WIDTH 1920
#define DEFAULT_GBUFFER_RESOLUTION_HEIGHT 1080

void dooms::graphics::DefferedRenderingFrameBuffer::Initialize
(
	const UINT32 resolutionWidth,
	const UINT32 resolutionHeight
)
{//with renderbuffer, can't do post-processing

	//Position
	FrameBuffer::AttachColorTextureToFrameBuffer(0, resolutionWidth, resolutionHeight);

	//Normal
	FrameBuffer::AttachColorTextureToFrameBuffer(1, resolutionWidth, resolutionHeight);

	//Albedo
	FrameBuffer::AttachColorTextureToFrameBuffer(2, resolutionWidth, resolutionHeight);

	//Depth
	FrameBuffer::AttachDepthTextureToFrameBuffer(resolutionWidth, resolutionHeight);

	for (UINT32 i = 0; i < 3; i++)
	{
		TextureView* const textureView = FrameBuffer::GetColorTextureView(i, graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER);
		D_ASSERT(IsValid(textureView));
		TextureViews[i] = textureView;
	}
}

dooms::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer()
	: FrameBuffer(DEFAULT_GBUFFER_RESOLUTION_WIDTH, DEFAULT_GBUFFER_RESOLUTION_HEIGHT)
{
	
	Initialize(DEFAULT_GBUFFER_RESOLUTION_WIDTH, DEFAULT_GBUFFER_RESOLUTION_HEIGHT);
}

dooms::graphics::DefferedRenderingFrameBuffer::DefferedRenderingFrameBuffer
(
	const UINT32 resolutionWidth,
	const UINT32 resolutionHeight
)
	: FrameBuffer(resolutionWidth, resolutionHeight)
{
	Initialize(resolutionWidth, resolutionHeight);
}

void dooms::graphics::DefferedRenderingFrameBuffer::BlitDepthBufferToScreenBuffer()
{
	FrameBuffer::BlitFrameBufferFromToFrameBuffer(this, nullptr, 0, 0, GetDefaultWidth(), GetDefaultHeight(), 0, 0, 1920, 1080, GraphicsAPI::eBufferBitType::DEPTH_BUFFER, GraphicsAPI::eImageInterpolation::IMAGE_INTERPOLATION_NEAREST);

}

void dooms::graphics::DefferedRenderingFrameBuffer::BindGBufferTextures()
{
	for (UINT32 i = 0; i < 3; i++)
	{
		D_ASSERT(IsValid(TextureViews[i]));
		TextureViews[i]->BindTexture(i, graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER);
	}
}

void dooms::graphics::DefferedRenderingFrameBuffer::UnBindGBufferTextures()
{
	for (UINT32 i = 0; i < 3; i++)
	{
		D_ASSERT(IsValid(TextureViews[i]));
		TextureViews[i]->UnBindTexture(i, graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER);
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
	
	ClearColorTexture(0, TARGET_COLORS[0][0], TARGET_COLORS[0][1], TARGET_COLORS[0][2], TARGET_COLORS[0][3]);
	ClearColorTexture(1, TARGET_COLORS[1][0], TARGET_COLORS[1][1], TARGET_COLORS[1][2], TARGET_COLORS[1][3]);
	ClearColorTexture(2, TARGET_COLORS[2][0], TARGET_COLORS[2][1], TARGET_COLORS[2][2], TARGET_COLORS[2][3]);
	//GraphicsAPI::ClearBuffer(GraphicsAPI::eBufferBitType::COLOR_BUFFER);
	//GraphicsAPI::ClearBuffer(GraphicsAPI::eBufferBitType::DEPTH_BUFFER);
	ClrearDepthTexture(GraphicsAPI::DEFAULT_MAX_DEPTH_VALUE);
	
}
