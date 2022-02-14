#pragma once

#include <Core.h>

#include "../../GraphicsPipeLineCamera.h"
#include <Rendering/Pipeline/PipeLines/DeferredRendering/DefferedRenderingFrameBuffer.h>

#include "DeferredRenderingPipeLineCamera.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS DeferredRenderingPipeLineCamera : public GraphicsPipeLineCamera
		{
			GENERATE_BODY()
		private:

		public:

			D_PROPERTY()
			graphics::DefferedRenderingFrameBuffer mDeferredRenderingFrameBuffer;

			DeferredRenderingPipeLineCamera();

			FrameBuffer* GetCameraFrameBuffer() override;
		};
	}
}

