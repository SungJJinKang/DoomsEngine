#include "DeferredRenderingPipeLineCamera.h"

dooms::graphics::DeferredRenderingPipeLineCamera::DeferredRenderingPipeLineCamera()
	: mDeferredRenderingFrameBuffer()
{
}

dooms::graphics::FrameBuffer* dooms::graphics::DeferredRenderingPipeLineCamera::GetCameraFrameBuffer()
{
	return &mDeferredRenderingFrameBuffer;
}
